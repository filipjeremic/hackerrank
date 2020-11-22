#!/bin/python3


# Time complexity: O(n)
# Space complexity: O(n)

# The logic:

# The numbers in this problem are extremely large and are handled as strings.
# The solution has two parts: mandatory and optimization.

# Mandatory part - here we attempt to transform A and B so that A | B = C with
# the minimum number of changes. For this we use a table which has every combination
# of A, B and C. So for each value of A and B (both 0..15, that is 0x0..0xF), we store
# how many changes are required and what are the resulting A and B to get A | B = C.
# The size of this table is 16x16x16 = 4096. We do this once because we don’t want to
# recalculate the same combinations. If this part fails, the numbers can’t be transformed
# with up to K changes and we print out -1.

# Optimization part - we use the remaining K to optimize. This part is simpler because
# if a bit in C is 0 there is nothing to optimize (because in this case, after the mandatory part,
# bit A and bit B are both 0, which is already optimal). When bit C is 1 there are 3 cases:

# | bit A | bit B |
# |   0   |   1   |
# |   1   |   0   |
# |   1   |   1   |

# We always want bit A to be 0 since A has priority. Therefore, bit B needs to be 1.
# In the first case, we already have those values and there is nothing to be done.
# In the second case we need to change both bit A and bit B, so two steps are required.
# In the third case all we need to do is set bit A to 0.
# Notice that this loop doesn’t end at the first failure because you can have a situation
# where K = 1 in case two. In this case you skip the transformation and continue checking
# because there might be a case three later on to ultimately use the last K.

# Important note - the output must be upper case to be accepted on HackerRank.

# In this solution (JavaScript) I utilized BigInt for printing output. Check out the other solutions
# for a base case (leading zeroes need to be skipped).


def int_bit(value: int, mask: int):
    return 1 if (value & mask) > 0 else 0


def get_mandatory_changes(a: int, b: int, c: int) -> tuple:
    total_change_count = 0
    new_a = 0
    new_b = 0

    i = 8
    while i > 0:
        a_bit = int_bit(a, i)
        b_bit = int_bit(b, i)
        c_bit = int_bit(c, i)

        i >>= 1

        change_count = ((c_bit ^ 1) * (a_bit + b_bit)) + (c_bit * ((a_bit | b_bit) ^ 1))

        total_change_count += change_count
        new_a = (new_a << 1) | (c_bit * a_bit)
        new_b = (new_b << 1) | (c_bit * (b_bit + change_count))

    return (total_change_count, new_a, new_b)


def get_mandatory_changes_table() -> list:
    n = 16
    t = []
    for a in range(n):
        ta = []
        for b in range(n):
            tb = []
            for c in range(n):
                tb.append(get_mandatory_changes(a, b, c))
            ta.append(tb)
        t.append(ta)
    return t


mandatory_changes_table = get_mandatory_changes_table()


def mandatory_changes(k: int, a: list, b: list, c: list) -> int:
    for i in range(len(a)):
        int_a = int(a[i], 16)
        int_b = int(b[i], 16)
        int_c = int(c[i], 16)

        changes = mandatory_changes_table[int_a][int_b][int_c]

        k -= changes[0]
        if k < 0:
            break

        a[i] = changes[1]
        b[i] = changes[2]
        c[i] = int_c

    return k


def optimize(k: int, a: int, b: int, c: int) -> tuple:
    total_change_count = 0
    new_a = 0
    new_b = 0

    i = 8
    while i > 0:
        a_bit = int_bit(a, i)
        b_bit = int_bit(b, i)
        c_bit = int_bit(c, i)
        change_count = a_bit + (b_bit ^ 1)

        i >>= 1

        if (c_bit == 0) or (change_count > k):
            new_a = (new_a << 1) | a_bit
            new_b = (new_b << 1) | b_bit
        else:
            k -= change_count
            total_change_count += change_count
            new_a = (new_a << 1) | 0
            new_b = (new_b << 1) | 1

    return (total_change_count, new_a, new_b)


def optimization_changes(k: int, a: list, b: list, c: list):
    for i in range(len(a)):
        if k == 0:
            break

        changes = optimize(k, a[i], b[i], c[i])

        k -= changes[0]

        a[i] = changes[1]
        b[i] = changes[2]


def trim_leading_zeroes(arr: list) -> list:
    for i in range(len(arr)):
        if arr[i] != 0:
            return arr[i:]
    return [0]


def a_or_b(k: int, a: list, b: list, c: list) -> None:
    k = mandatory_changes(k, a, b, c)

    if k < 0:
        print(-1)
        return

    optimization_changes(k, a, b, c)

    a = trim_leading_zeroes(a)
    b = trim_leading_zeroes(b)

    print("".join(map(lambda x: hex(x)[2:].upper(), a)))
    print("".join(map(lambda x: hex(x)[2:].upper(), b)))


if __name__ == "__main__":
    q = int(input())
    for i in range(q):
        k = int(input())
        a = list(input())
        b = list(input())
        c = list(input())
        a_or_b(k, a, b, c)

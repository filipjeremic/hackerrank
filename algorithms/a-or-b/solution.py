#!/bin/python3


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

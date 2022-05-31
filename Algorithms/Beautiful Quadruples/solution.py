def read_input():
    return list(map(int, input().split(" ")))


def get_next_pow_2(n):
    if n == 0:
        return 1

    result = 1
    while result <= n:
        result *= 2

    return result


def get_initial_carry_matrix(low_value, high_value):
    N = get_next_pow_2(high_value)

    initial_carry_matrix = [[0]*N for i in range(low_value + 1)]

    for i in range(1, low_value + 1):
        for j in range(i, high_value + 1):
            initial_carry_matrix[i][i ^ j] = 1

    return initial_carry_matrix


def reduce_matrix(carry_matrix):
    rows = len(carry_matrix)
    cols = len(carry_matrix[0])

    for i in range(rows - 1, 1, -1):
        for j in range(cols):
            carry_matrix[i-1][j] += carry_matrix[i][j]


def xor_carry_matrix(B, carry_matrix):
    N = len(carry_matrix[0])

    xor_matrix = [[0]*N for i in range(B + 1)]

    for i in range(1, B+1):
        for j in range(N):
            xor_matrix[i][i ^ j] = carry_matrix[i][j]

    return xor_matrix


def calculate_result(A, xor_matrix):
    result = 0

    for i in range(1, A+1):
        result += sum(xor_matrix[i])
        result -= xor_matrix[i][i]

    return result


def solution():
    values = read_input()
    values.sort()

    carry_matrix = get_initial_carry_matrix(values[2], values[3])
    reduce_matrix(carry_matrix)

    carry_matrix = xor_carry_matrix(values[1], carry_matrix)
    reduce_matrix(carry_matrix)

    print(calculate_result(values[0], carry_matrix))


if __name__ == "__main__":
    solution()

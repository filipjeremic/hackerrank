#!/bin/python3

# Note - a recursive solution won't work here (stack overflow)


def max_subset_sum(arr):
    sum_with_current = sum_with_previous = 0

    for x in arr:
        if x <= 0:
            sum_with_current = sum_with_previous = max(sum_with_current, sum_with_previous)
            continue

        sum_with_current += x

        if sum_with_previous >= sum_with_current:
            sum_with_current = sum_with_previous
            continue

        sum_with_current, sum_with_previous = sum_with_previous, sum_with_current

    return max(sum_with_current, sum_with_previous)


if __name__ == "__main__":
    input()
    arr = list(map(int, input().rstrip().split()))
    print(max_subset_sum(arr))

#!/bin/python3

# Iterative solution

# Time complexity: O(n)
# Space complexity: O(1)

# Note - a recursive solution won't work here (stack overflow)

# The logic:
#     - every value that you use, the adjacent one you can't
#     - therefore you have to skip everything that is not required
#     - when you skip a value you get the maximum sum so far (this restarts the process of considering values)
#     - negative values are not considered
#     - for positive values you have to check what's larger, max_sum(i - 2) + value or max_sum(i - 1)
#     - if max_sum(i - 2) + value is larger you consider the value (here you have to swap the sums because you added a value)
#     - if max_sum(i - 1) is larger you don't consider value


def maxSubsetSum(arr):
    appendable = notAppendable = 0

    for x in arr:
        if x <= 0:
            appendable = notAppendable = max(appendable, notAppendable)
            continue

        appendable += x

        if notAppendable >= appendable:
            appendable = notAppendable
            continue

        appendable, notAppendable = notAppendable, appendable

    return max(appendable, notAppendable)


if __name__ == '__main__':
    input()
    arr = list(map(int, input().rstrip().split()))

    print(maxSubsetSum(arr))

#!/bin/python3

# Note - a recursive solution won't work here (stack overflow)


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


if __name__ == "__main__":
    input()
    arr = list(map(int, input().rstrip().split()))
    print(maxSubsetSum(arr))

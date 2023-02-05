#!/bin/python3

# Note - a recursive solution won't work in Python3
# A stack overflow error occurs
# And if the recursion limit is increased, a segmentation fault occurs


import os


def candies(n, arr):
    candy = [1] * n

    for i in range(1, n):
        if arr[i] > arr[i - 1]:
            candy[i] = candy[i - 1] + 1

    for i in range(n - 2, -1, -1):
        if arr[i] > arr[i + 1] and candy[i] < (candy[i + 1] + 1):
            candy[i] = candy[i + 1] + 1

    return sum(candy)


if __name__ == "__main__":
    fptr = open(os.environ["OUTPUT_PATH"], "w")

    n = int(input().strip())

    arr = []

    for _ in range(n):
        arr_item = int(input().strip())
        arr.append(arr_item)

    result = candies(n, arr)

    fptr.write(str(result) + "\n")

    fptr.close()

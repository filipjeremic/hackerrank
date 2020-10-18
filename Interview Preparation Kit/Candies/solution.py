#!/bin/python3

# Note - a recursive solution won't work in Python3
# You will get a stack overflow error
# And in case you increase the recursion limit you will get a segmentation fault
# Check out the other languages for a recursive solution


# The logic:
#    - every child must get at least 1 piece of candy
#    - the amout of candy a child gets depends only on its neighbors
#    - if the childs rating is higher than that of its previous neighbor,
#          it gets 1 piece of candy more than the previous neighbor, otherwise it gets 1
#    - same rule applies for its next neighbor
#    - the child gets the greater (max) of the two values pieces of candy

# Time complexity: O(n)
# Space complexity: O(n)

import os

# Iterative solution


def candies(n, arr):
    candy = [1] * n
    for i in range(1, n):
        if arr[i] > arr[i - 1]:
            candy[i] = candy[i - 1] + 1
    for i in range(n - 2, -1, -1):
        if arr[i] > arr[i + 1]:
            candy[i] = max(candy[i], candy[i + 1] + 1)
    return sum(candy)


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    arr = []

    for _ in range(n):
        arr_item = int(input())
        arr.append(arr_item)

    result = candies(n, arr)

    fptr.write(str(result) + '\n')

    fptr.close()

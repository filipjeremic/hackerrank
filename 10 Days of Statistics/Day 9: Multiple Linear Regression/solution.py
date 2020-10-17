import numpy

# The formula is in the 'Tutorial' tab
# Matrix multiplication operator '@' was introduced in Python 3.5.0


if __name__ == '__main__':
    n = int(input().strip().split(' ')[1])

    X, Y = [], []

    for _ in range(n):
        arr = list(map(float, input().strip().split(' ')))
        X.append([1] + arr[0: -1])
        Y.append(arr[-1])

    X, Y = map(numpy.array, (X, Y))

    XT = numpy.transpose(X)

    B = numpy.linalg.inv(XT @ X) @ XT @ Y

    q = int(input())

    X = []
    for _ in range(q):
        X.append([1] + list(map(float, input().strip().split(' '))))

    X = numpy.array(X)

    Y = X @ B

    print('\n'.join(('{:.2f}'.format(value) for value in Y)))

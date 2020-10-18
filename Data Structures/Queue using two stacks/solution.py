#!/usr/bin/python3.8

# The solution is NOT thread safe (it is not required)

class Queue:

    def __init__(self):
        # O(1)
        # One stack for input and one for output
        self.enqueueStack = []
        self.dequeueStack = []

    def enqueue(self, value):
        # amortized O(1)
        self.enqueueStack.append(value)

    def dequeue(self):
        # amortized O(1)
        # only transfer when the output stack is empty
        self.__check_and_transfer()
        # checking again because the source stack can also be empty (we transferred nothing)
        if not self.dequeueStack:
            return None
        return self.dequeueStack.pop()

    def __check_and_transfer(self):
        # O(n), where n is the number of elements in enqueueStack
        if self.dequeueStack:
            return
        self.__transfer()

    def __transfer(self):
        # O(n), where n is the number of elements in enqueueStack
        while self.enqueueStack:
            self.dequeueStack.append(self.enqueueStack.pop())

    def front(self):
        # amortized O(1)
        self.__check_and_transfer()
        if not self.dequeueStack:
            return None
        return self.dequeueStack[-1]


if __name__ == "__main__":

    q = Queue()

    n = int(input())

    for i in range(n):
        arr = list(map(int, input().strip().split(' ')))

        if arr[0] == 2:
            q.dequeue()
        elif arr[0] == 3:
            print(q.front())
        else:
            q.enqueue(arr[1])

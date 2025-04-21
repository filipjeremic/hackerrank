#!/usr/bin/python3.8


class Queue:
    # O(1)
    def __init__(self):
        self.enqueueStack = []
        self.dequeueStack = []

    # Amortized O(1)
    def enqueue(self, value):
        self.enqueueStack.append(value)

    # Amortized O(1) - only transfer when the output stack is empty
    def dequeue(self):
        self.__check_and_transfer()
        # checking again because the source stack can also be empty (we transferred nothing)
        if not self.dequeueStack:
            return None
        return self.dequeueStack.pop()

    # Amortized O(1)
    def __check_and_transfer(self):
        if self.dequeueStack:
            return
        self.__transfer()

    # Amortized O(n), where n is the number of elements in enqueueStack
    def __transfer(self):
        while self.enqueueStack:
            self.dequeueStack.append(self.enqueueStack.pop())

    # Amortized O(1)
    def front(self):
        self.__check_and_transfer()
        if not self.dequeueStack:
            return None
        return self.dequeueStack[-1]


if __name__ == "__main__":
    q = Queue()

    n = int(input())

    for i in range(n):
        arr = list(map(int, input().strip().split(" ")))

        if arr[0] == 2:
            q.dequeue()
        elif arr[0] == 3:
            print(q.front())
        else:
            q.enqueue(arr[1])

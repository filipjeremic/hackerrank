package main

import (
	"errors"
	"fmt"
)

type Stack interface {
	push(value int)
	pop() (int, error)
	top() (int, error)
	isEmpty() bool
}

type SimpleStack struct {
	values []int
}

func (s *SimpleStack) push(value int) {
	s.values = append(s.values, value)
}

func (s *SimpleStack) pop() (int, error) {
	if len(s.values) == 0 {
		return 0, errors.New("can't pop from an empty stack")
	}

	lastIndex := len(s.values) - 1
	value := s.values[lastIndex]
	s.values = s.values[:lastIndex]
	return value, nil
}

func (s *SimpleStack) top() (int, error) {
	if len(s.values) == 0 {
		return 0, errors.New("can't get the top value of an empty stack")
	}

	return s.values[len(s.values)-1], nil
}

func (s *SimpleStack) isEmpty() bool {
	return len(s.values) == 0
}

type Queue interface {
	enqueue(value int)
	dequeue() (int, error)
	front() (int, error)
}

type SimpleQueue struct {
	enqueueStack Stack
	dequeueStack Stack
}

func (q *SimpleQueue) enqueue(value int) {
	q.enqueueStack.push(value)
}

func (q *SimpleQueue) transfer() {
	for !q.enqueueStack.isEmpty() {
		value, _ := q.enqueueStack.pop()
		q.dequeueStack.push(value)
	}
}

func (q *SimpleQueue) transferIfNeeded() {
	if q.dequeueStack.isEmpty() {
		q.transfer()
	}
}

func getEmptyQueueError() (int, error) {
	return 0, errors.New("the queue is empty")
}

func (q *SimpleQueue) dequeue() (int, error) {
	q.transferIfNeeded()

	if q.dequeueStack.isEmpty() {
		return getEmptyQueueError()
	}

	return q.dequeueStack.pop()
}

func (q *SimpleQueue) front() (int, error) {
	q.transferIfNeeded()

	if q.dequeueStack.isEmpty() {
		return getEmptyQueueError()
	}

	return q.dequeueStack.top()
}

func main() {

	var q Queue = &SimpleQueue{&SimpleStack{[]int{}}, &SimpleStack{[]int{}}}

	n, t, v := 0, 0, 0
	_, _ = fmt.Scanf("%d", &n)

	for i := 0; i < n; i++ {
		_, _ = fmt.Scanf("%d", &t)

		switch t {
		case 1:
			_, _ = fmt.Scanf("%d", &v)
			q.enqueue(v)
		case 2:
			q.dequeue()
		case 3:
			v, _ = q.front()
			fmt.Println(v)
		}
	}
}

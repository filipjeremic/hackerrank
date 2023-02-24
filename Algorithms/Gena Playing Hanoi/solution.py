#!/bin/python3


from collections import deque
from copy import deepcopy
from functools import cmp_to_key


def read_input_data() -> list[int]:
    input()
    return list(map(int, input().rstrip().split()))


def transform_input_data(data: list[int]) -> list[list[int]]:
    result = [[], [], [], []]
    for i in range(len(data) - 1, -1, -1):
        result[data[i] - 1].append(i)
    return result


def compare(lhs: list[int], rhs: list[int]) -> int:
    if len(lhs) == 0:
        return 0
    if len(rhs) == 0:
        return -1
    return rhs[-1] - lhs[-1]


def sort_state(state: list[list[int]]):
    state[1:] = sorted(state[1:], key=cmp_to_key(compare))


def is_end_state(state: list[list[int]]) -> bool:
    return len(state[1]) == 0 and len(state[2]) == 0 and len(state[3]) == 0


def solution(initial_state: list[list[int]]) -> int:
    sort_state(initial_state)
    state_queue = deque([[initial_state, 0]])
    visited_states = {str(initial_state)}
    while len(state_queue) > 0:
        [current_state, current_step] = state_queue.popleft()
        if is_end_state(current_state):
            return current_step
        for i, to_stack in enumerate(current_state):
            for j, from_stack in enumerate(current_state):
                if len(from_stack) == 0:
                    continue
                if len(to_stack) > 0 and from_stack[-1] >= to_stack[-1]:
                    continue
                new_state = deepcopy(current_state)
                new_state[i].append(new_state[j].pop())
                sort_state(new_state)
                new_state_string = str(new_state)
                if new_state_string in visited_states:
                    continue
                visited_states.add(new_state_string)
                state_queue.append([new_state, current_step + 1])
    return 0


if __name__ == "__main__":
    input_data = read_input_data()
    data = transform_input_data(input_data)
    print(solution(data))

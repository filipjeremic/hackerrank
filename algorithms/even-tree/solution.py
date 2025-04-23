#!/bin/python3


def even_forest(m, current_node):
    if current_node not in m:
        return 1, 0
    result = 0
    children_count = 0
    for child_node in m[current_node]:
        child_children_count, child_result = even_forest(m, child_node)
        result += child_result
        if child_children_count % 2 == 0:
            result += 1
        else:
            children_count += child_children_count
    return children_count + 1, result


def read_input():
    _, edge_count = map(int, input().rstrip().split())
    m = {}
    for i in range(edge_count):
        node_to, node_from = map(int, input().rstrip().split())
        m.setdefault(node_from, set()).add(node_to)
    return m


if __name__ == '__main__':

    m = read_input()
    _, result = even_forest(m, 1)

    print(result)

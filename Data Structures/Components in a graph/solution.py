#!/bin/python3


def read_data():
    n = int(input())
    return [tuple(map(int, input().split())) for _ in range(n)]


def components_in_graph(data):
    m = {}
    for a, b in data:
        has_a, has_b = a in m, b in m

        if not has_a and not has_b:
            new_list = [a, b]
            m[a], m[b] = new_list, new_list
            continue

        if has_a and has_b:
            list_a, list_b = m[a], m[b]
            if list_a == list_b:
                continue

            size_a, size_b = len(list_a), len(list_b)
            list_small, list_large = (
                list_a if size_a < size_b else list_b,
                list_a if size_a >= size_b else list_b,
            )
            for i in list_small:
                m[i] = list_large
                list_large.append(i)
            continue

        value_to_insert, insert_list = b if has_a else a, m[a if has_a else b]
        insert_list.append(value_to_insert)
        m[value_to_insert] = insert_list

    return len(min(m.values(), key=len)), len(max(m.values(), key=len))


if __name__ == "__main__":
    print(*components_in_graph(read_data()))

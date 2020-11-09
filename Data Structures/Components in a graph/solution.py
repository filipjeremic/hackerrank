# Time complexity: O(n)
# Space complexity: O(n)

# The logic:
#     - you need to keep track of which values are connected (the order is irrelevant)
#     - this is done by having a map which says which value is in which list (lists are unique and shared)
#     - when a new pair is examined there a X cases
#         1) both values are new -> new list and map entries
#         2) both values are not new and they are in the same list already -> do nothing
#         3) both values are not new and they are not in the same list -> update the map entries for
#             the values in one list to point to the other list and add the values from one list to the
#             other list (I chose looping and modifying the smaller list because of performance)
#         4) one value is new -> add it to the list of the other value and create the map entry for it


def read_data():
    n = int(input())
    return [tuple(map(int, input().split())) for _ in range(n)]


def components_in_graph(data):
    m = {}
    for a, b in data:
        has_a, has_b = a in m, b in m

        if not has_a and not has_b:
            l = [a, b]
            m[a], m[b] = l, l
            continue

        if has_a and has_b:
            la, lb = m[a], m[b]
            if la == lb:
                continue

            size_a, size_b = len(la), len(lb)
            l_small, l_large = la if size_a < size_b else lb, la if size_a >= size_b else lb
            for i in l_small:
                m[i] = l_large
                l_large.append(i)
            continue

        value_to_insert, where_to_insert = b if has_a else a, m[a if has_a else b]
        where_to_insert.append(value_to_insert)
        m[value_to_insert] = where_to_insert

    return len(min(m.values(), key=len)), len(max(m.values(), key=len))


if __name__ == "__main__":
    print(*components_in_graph(read_data()))

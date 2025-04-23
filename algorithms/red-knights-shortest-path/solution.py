#!/bin/python3


def is_possible(sr, sc, er, ec):
    if (sr + er) % 2 != 0:
        return False

    if (sc + ec) % 2 != 0:
        return (er - sr + 2) % 4 == 0

    return (er - sr) % 4 == 0


def get_shortest_path(n, sr, sc, er, ec):
    moveCount = 0
    path = ""

    while sr != er or sc != ec:
        if sr > er:
            # moving up
            left_up_first = ((ec - sc) * 2) < (sr - er)
            if sc > 0 and ((sc >= ec) or left_up_first):
                path += "UL"
                sc -= 1
            else:
                path += "UR"
                sc += 1
            sr -= 2
        elif sr < er:
            # moving down or right
            if (ec - sc) * 2 > er - sr:
                # moving right
                path += "R"
                sc += 2
            else:
                # moving down
                right_down_first = (sc - ec) * 2 < er - sr
                if (sc < n - 1 and (sc <= ec or right_down_first)):
                    path += "LR"
                    sc += 1
                else:
                    path += "LL"
                    sc -= 1
                sr += 2
        else:
            if ec < sc:
                path += "L"
                sc -= 2
            else:
                path += "R"
                sc += 2

        moveCount += 1
        path += " "

    return moveCount, path


def print_shortest_path(n, sr, sc, er, ec):
    if not is_possible(sr, sc, er, ec):
        print("Impossible")
        return

    moveCount, path = get_shortest_path(n, sr, sc, er, ec)
    print(moveCount)
    print(path)


if __name__ == '__main__':
    n = int(input().strip())

    coordinates = input().rstrip().split()

    sr = int(coordinates[0])
    sc = int(coordinates[1])
    er = int(coordinates[2])
    ec = int(coordinates[3])

    print_shortest_path(n, sr, sc, er, ec)

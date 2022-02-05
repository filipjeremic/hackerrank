package main

/*

Time complexity: O(n)
Space complexity: O(n) - because of the result string

The logic:

This problem is not too complex. Basically, one just needs to do the right
calculation to figure out whether or not it is possible to reach the
destination and if it is, align the conditions properly.

It is beneficial to understand that the red knight will never go back
vertically. So if he needs to go up, he will only go up or sideways. Same
thing for going down. Additionally, he can only stand on the green fields
that are marked (recursively). This shows us the positions which he can reach.
If the end position is on one of these fields, it is reachable, otherwise it
is "Impossible".

The tricky parts are the corner cases and priorities. Obviously, you can't go
over field bounds. But additionally you need to prioritize moves. For example
 - the moves from (6, 1) to (0, 2) are UL UR UR, not UR UL UR or UR UR UL,
 because UL has priority. So, even though the end position is to the right,
 you have to go to the left first. When going down, LR has priority over LL,
 but R has priority over LR. All this needs to be taken into consideration.
 When the red knight is in the row where the end is, the movement is trivial
 - just go left or right.

*/

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func isOdd(number int) bool {
	return number%2 != 0
}

func parseInt10(number string) int {
	n, _ := strconv.ParseInt(number, 10, 32)
	return int(n)
}

func readData() (int, int, int, int, int) {
	reader := bufio.NewReader(os.Stdin)

	nString, _ := reader.ReadString('\n')
	nString = strings.TrimSpace(nString)
	n := parseInt10(nString)

	coordinatesLine, _ := reader.ReadString('\n')
	coordinatesLine = strings.TrimSpace(coordinatesLine)
	c := strings.Split(coordinatesLine, " ")

	sr, sc, er, ec := parseInt10(c[0]), parseInt10(c[1]), parseInt10(c[2]), parseInt10(c[3])

	return n, sr, sc, er, ec
}

func isPossible(sr, sc, er, ec int) bool {
	if isOdd(er + sr) {
		return false
	}

	if isOdd(ec + sc) {
		return (er-sr+2)%4 == 0
	}

	return (er-sr)%4 == 0
}

func getPath(n, sr, sc, er, ec int) (int, string) {
	path := strings.Builder{}
	moveCount := 0

	for sr != er || sc != ec {
		if sr > er {
			// moving up
			path.WriteByte('U')

			leftUpFirst := ((ec - sc) * 2) < (sr - er)
			if sc > 0 && ((sc >= ec) || leftUpFirst) {
				path.WriteByte('L')
				sc--
			} else {
				path.WriteByte('R')
				sc++
			}
			sr -= 2
		} else if sr < er {
			// moving down or right

			if (ec-sc)*2 > er-sr {
				// moving right
				sc += 2
				path.WriteByte('R')
			} else {
				//moving down
				path.WriteByte('L')

				rightDownFirst := (sc-ec)*2 < (er - sr)
				if sc < n-1 && ((sc <= ec) || rightDownFirst) {
					path.WriteByte('R')
					sc++
				} else {
					path.WriteByte('L')
					sc--
				}

				sr += 2
			}
		} else {
			if ec < sc {
				path.WriteByte('L')
				sc -= 2
			} else {
				path.WriteByte('R')
				sc += 2
			}
		}

		moveCount++
		path.WriteByte(' ')
	}

	return moveCount, path.String()
}

func solution(n, sr, sc, er, ec int) {
	if !isPossible(sr, sc, er, ec) {
		fmt.Println("Impossible")
		return
	}

	moveCount, path := getPath(n, sr, sc, er, ec)
	fmt.Println(moveCount)
	fmt.Println(path)
}

func main() {
	// startRow, startCol, endRow, endCol
	n, sr, sc, er, ec := readData()
	solution(n, sr, sc, er, ec)
}

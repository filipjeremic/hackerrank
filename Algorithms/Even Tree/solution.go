package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

func readInputLine(reader *bufio.Reader) (x, y int, err error) {
	line, err := reader.ReadString('\n')
	if err != nil && err != io.EOF {
		return
	}

	arr := strings.Split(strings.TrimSpace(line), " ")

	x64, err := strconv.ParseInt(arr[0], 10, 32)
	if err != nil {
		return
	}

	y64, err := strconv.ParseInt(arr[1], 10, 32)
	if err != nil {
		return
	}

	return int(x64), int(y64), err
}

func evenForest(m map[int]map[int]bool, currentNode int) (childrenCountReturn, result int) {
	if children, currentNodeHasChildren := m[currentNode]; currentNodeHasChildren {
		for childNode := range children {
			childrenCount, childResult := evenForest(m, childNode)
			result += childResult
			if childrenCount%2 == 0 {
				result++
			} else {
				childrenCountReturn += childrenCount
			}
		}
		childrenCountReturn++
		return
	}

	return 1, 0
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	_, edgeCount, err := readInputLine(reader)
	if err != nil {
		fmt.Println(err)
		return
	}

	m := make(map[int]map[int]bool)

	for i := 0; i < edgeCount; i++ {
		nodeTo, nodeFrom, err := readInputLine(reader)
		if err != nil {
			fmt.Println(err)
			return
		}

		if _, nodeFromIsInMap := m[nodeFrom]; !nodeFromIsInMap {
			m[nodeFrom] = make(map[int]bool)
		}
		m[nodeFrom][nodeTo] = true
	}

	_, result := evenForest(m, 1)
	fmt.Println(result)
}

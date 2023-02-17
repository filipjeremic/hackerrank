package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

func checkError(err error) {
	if err != nil {
		panic(err)
	}
}

func readData() [][2]int {
	reader := bufio.NewReader(os.Stdin)

	line, err := reader.ReadString('\n')
	checkError(err)

	n, err := strconv.Atoi(strings.TrimSpace(line))
	checkError(err)

	data := make([][2]int, n)
	for i := 0; i < n; i++ {
		line, err = reader.ReadString('\n')
		if err != io.EOF {
			checkError(err)
		}

		pair := strings.Fields(line)

		a, err := strconv.Atoi(strings.TrimSpace(pair[0]))
		checkError(err)
		b, err := strconv.Atoi(strings.TrimSpace(pair[1]))
		checkError(err)

		data[i][0], data[i][1] = a, b
	}

	return data
}

func getMinMax(m map[int]*[]int) *[2]int {
	minSize := 30000
	maxSize := 0

	for _, list := range m {
		currentSize := len(*list)

		if currentSize < minSize {
			minSize = currentSize
		}

		if currentSize > maxSize {
			maxSize = currentSize
		}
	}

	return &[2]int{minSize, maxSize}
}

func componentsInGraph(data [][2]int) *[2]int {
	m := make(map[int]*[]int)

	for _, pair := range data {
		a, b := pair[0], pair[1]

		listA, hasA := m[a]
		listB, hasB := m[b]

		if !hasA && !hasB {
			newList := make([]int, 2)
			newList[0], newList[1] = a, b
			m[a], m[b] = &newList, &newList
			continue
		}

		if hasA && hasB {
			if listA == listB {
				continue
			}

			listSmall, listLarge := listA, listB
			if len(*listA) > len(*listB) {
				listSmall, listLarge = listB, listA
			}

			*listLarge = append(*listLarge, *listSmall...)

			for _, value := range *listSmall {
				m[value] = listLarge
			}

			continue
		}

		valueToInsert := a
		insertList := listB
		if hasA {
			valueToInsert = b
			insertList = listA
		}

		*insertList = append(*insertList, valueToInsert)
		m[valueToInsert] = insertList
	}

	return getMinMax(m)
}

func main() {
	data := readData()
	result := componentsInGraph(data)
	fmt.Printf("%d %d\n", result[0], result[1])
}

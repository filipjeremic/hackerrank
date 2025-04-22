package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

func readInput() []int32 {
	reader := bufio.NewReader(os.Stdin)

	reader.ReadString('\n')

	line, err := reader.ReadString('\n')

	if err != io.EOF && err != nil {
		panic(err)
	}

	arrString := strings.Fields(line)

	arr := make([]int32, len(arrString))

	for i := 0; i < len(arr); i++ {
		value, err := strconv.ParseInt(arrString[i], 10, 32)
		if err != nil {
			panic(err)
		}
		arr[i] = int32(value)
	}

	return arr
}

func max(a, b int32) int32 {
	if a > b {
		return a
	}
	return b
}

func maxSubsetSum(arr []int32) int32 {

	sumWithCurrent := int32(0)
	sumWithPrevious := int32(0)

	for _, value := range arr {
		if value <= 0 {
			sumWithCurrent = max(sumWithCurrent, sumWithPrevious)
			sumWithPrevious = sumWithCurrent
			continue
		}

		sumWithCurrent += value

		if sumWithPrevious >= sumWithCurrent {
			sumWithCurrent = sumWithPrevious
			continue
		}

		sumWithCurrent, sumWithPrevious = sumWithPrevious, sumWithCurrent
	}

	return max(sumWithCurrent, sumWithPrevious)
}

func main() {
	fmt.Println(maxSubsetSum(readInput()))
}

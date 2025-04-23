package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

func readValues() []int {
	reader := bufio.NewReader(os.Stdin)

	line, _, _ := reader.ReadLine()

	stringValues := strings.Split(string(line), " ")
	intValues := make([]int, len(stringValues))

	for i, stringValue := range stringValues {
		intValues[i], _ = strconv.Atoi(stringValue)
	}

	return intValues
}

func getNextPow2(n uint64) uint64 {
	if n == 0 {
		return 1
	}

	var result uint64 = 1

	for result <= n {
		result *= 2
	}

	return result
}

func getInitialCarryMatrix(lowValue uint64, highValue uint64) [][]uint64 {
	N := getNextPow2(highValue)

	initialCarryMatrix := make([][]uint64, lowValue+1)

	for i, _ := range initialCarryMatrix {
		initialCarryMatrix[i] = make([]uint64, N)

		for j := i; j <= int(highValue); j++ {
			initialCarryMatrix[i][i^j] = 1
		}
	}

	return initialCarryMatrix
}

func reduceMatrix(carryMatrix [][]uint64) {
	rows := len(carryMatrix)
	cols := len(carryMatrix[0])

	for i := rows - 1; i > 1; i-- {
		for j := 0; j < cols; j++ {
			carryMatrix[i-1][j] += carryMatrix[i][j]
		}
	}
}

func xorCarryMatrix(B int, carryMatrix [][]uint64) [][]uint64 {
	N := len(carryMatrix[0])

	xorMatrix := make([][]uint64, B+1)

	for i, _ := range xorMatrix {
		xorMatrix[i] = make([]uint64, N)

		for j := 0; j < N; j++ {
			xorMatrix[i][i^j] = carryMatrix[i][j]
		}
	}

	return xorMatrix
}

func calculateResult(A int, xorMatrix [][]uint64) uint64 {
	var result uint64 = 0

	for i := 1; i <= A; i++ {
		for j, n := range xorMatrix[i] {
			if i != j {
				result += n
			}
		}
	}

	return result
}

func main() {

	values := readValues()

	sort.Ints(values)

	carryMatrix := getInitialCarryMatrix(uint64(values[2]), uint64(values[3]))
	reduceMatrix(carryMatrix)

	carryMatrix = xorCarryMatrix(values[1], carryMatrix)
	reduceMatrix(carryMatrix)

	fmt.Println(calculateResult(values[0], carryMatrix))
}

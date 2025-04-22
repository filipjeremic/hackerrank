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
	if err != io.EOF && err != nil {
		panic(err)
	}
}

func readInt32(reader *bufio.Reader) int32 {
	iString, err := reader.ReadString('\n')
	checkError(err)
	i, err := strconv.ParseInt(strings.TrimSpace(iString), 10, 32)
	checkError(err)
	return int32(i)
}

func readRatings() []int32 {
	reader := bufio.NewReader(os.Stdin)

	n := readInt32(reader)

	ratings := make([]int32, n)
	for i := int32(0); i < n; i++ {
		rating := readInt32(reader)
		ratings[i] = rating
	}

	return ratings
}

func candies(ratings []int32) int64 {
	n := len(ratings)

	candy := make([]int64, n)

	for i := range candy {
		candy[i] = 1
	}

	for i := 1; i < n; i++ {
		if ratings[i] > ratings[i-1] {
			candy[i] = candy[i-1] + 1
		}
	}

	for i := n - 2; i >= 0; i-- {
		if (ratings[i] > ratings[i+1]) && (candy[i] < candy[i+1]+1) {
			candy[i] = candy[i+1] + 1
		}
	}

	result := int64(0)
	for _, v := range candy {
		result += v
	}

	return result
}

func main() {
	ratings := readRatings()
	fmt.Println(candies(ratings))
}

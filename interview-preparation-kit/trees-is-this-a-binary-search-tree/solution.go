package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

type Node struct {
	value int
	left  *Node
	right *Node
}

func readData() []int {
	reader := bufio.NewReader(os.Stdin)

	reader.ReadString('\n')

	line, err := reader.ReadString('\n')

	if err != io.EOF && err != nil {
		panic(err)
	}

	arrString := strings.Fields(line)

	arrInt := make([]int, len(arrString))

	for index, stringValue := range arrString {
		intValue, err := strconv.Atoi(stringValue)
		if err != nil {
			panic(err)
		}
		arrInt[index] = intValue
	}

	return arrInt
}

func formTree(arr []int, startIndex, endIndex int) *Node {
	if startIndex == endIndex {
		return nil
	}

	middleIndex := startIndex + (endIndex-startIndex)/2

	root := new(Node)
	root.value = arr[middleIndex]
	root.left = formTree(arr, startIndex, middleIndex)
	root.right = formTree(arr, middleIndex+1, endIndex)

	return root
}

func checkBST_recursive(root *Node, min, max int) bool {
	if root == nil {
		return true
	}

	v := root.value

	return v > min && v < max && checkBST_recursive(root.left, min, v) && checkBST_recursive(root.right, v, max)
}

func checkBST(root *Node) bool {
	return checkBST_recursive(root, -1, 10001)
}

func main() {
	arr := readData()
	tree := formTree(arr, 0, len(arr))
	if checkBST(tree) {
		fmt.Println("Yes")
	} else {
		fmt.Println("No")
	}
}

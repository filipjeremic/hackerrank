package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

func readInputData() []int {
	reader := bufio.NewReader(os.Stdin)

	reader.ReadString('\n')
	line, err := reader.ReadString('\n')

	if err != io.EOF && err != nil {
		panic("Reading input failed")
	}

	inputStringArray := strings.Split(strings.TrimSpace(line), " ")
	inputIntArray := make([]int, len(inputStringArray))

	for index, stringValue := range inputStringArray {
		intValue, err := strconv.Atoi(stringValue)
		if err != nil {
			panic(fmt.Sprintf("String to int conversion failed for '%v'", stringValue))
		}
		inputIntArray[index] = intValue
	}

	return inputIntArray
}

type State struct {
	rods [4][]int
	step int
}

func createInitialState(inputData []int) *State {
	initialState := &State{[4][]int{}, 0}
	for i := len(inputData) - 1; i >= 0; i-- {
		rodIndex := inputData[i] - 1
		diskSize := i
		initialState.rods[rodIndex] = append(initialState.rods[rodIndex], diskSize)
	}
	initialState.sort()
	return initialState
}

func isWrongOrder(lhs, rhs []int) bool {
	rhsLen := len(rhs)

	if rhsLen == 0 {
		return false
	}

	lhsLen := len(lhs)

	if lhsLen == 0 {
		return true
	}

	return lhs[lhsLen-1] < rhs[rhsLen-1]
}

func (s *State) sort() {
	if isWrongOrder(s.rods[2], s.rods[3]) {
		s.rods[2], s.rods[3] = s.rods[3], s.rods[2]
	}

	if isWrongOrder(s.rods[1], s.rods[2]) {
		s.rods[1], s.rods[2] = s.rods[2], s.rods[1]
	}

	if isWrongOrder(s.rods[2], s.rods[3]) {
		s.rods[2], s.rods[3] = s.rods[3], s.rods[2]
	}
}

func (s *State) isGoalState() bool {
	return (len(s.rods[1]) == 0) && (len(s.rods[2]) == 0) && (len(s.rods[3]) == 0)
}

func (s *State) copy() *State {
	stateCopy := &State{[4][]int{}, s.step}
	for index, rod := range s.rods {
		if rod == nil {
			continue
		}
		stateCopy.rods[index] = make([]int, len(rod))
		copy(stateCopy.rods[index], rod)
	}
	return stateCopy
}

func (s *State) String() string {
	return fmt.Sprintf("%v", s.rods)
}

func solution(initialState *State) int {
	stateQueue := make(chan *State, 20000)
	stateQueue <- initialState

	visitedStates := map[string]*State{initialState.String(): initialState}

	initCopy := initialState.copy()
	visitedStates[initCopy.String()] = initCopy
	visitedStates[initialState.String()] = initialState

	for currentState := range stateQueue {
		currentStep := currentState.step
		if currentState.isGoalState() {
			return currentStep
		}
		currentRods := currentState.rods

		for toIndex, toRod := range currentRods {
			for fromIndex, fromRod := range currentRods {
				fromRodLen := len(fromRod)
				if fromRodLen == 0 {
					continue
				}

				toRodLen := len(toRod)
				valueToMove := fromRod[fromRodLen-1]
				if (toRodLen > 0) && (valueToMove >= toRod[toRodLen-1]) {
					continue
				}

				newState := currentState.copy()
				newState.rods[toIndex] = append(newState.rods[toIndex], valueToMove)
				newState.rods[fromIndex] = newState.rods[fromIndex][:fromRodLen-1]
				newState.sort()
				newState.step += 1

				if _, stateAlreadyVisited := visitedStates[newState.String()]; !stateAlreadyVisited {
					visitedStates[newState.String()] = newState
					stateQueue <- newState
				}
			}
		}
	}

	return 0
}

func main() {
	inputData := readInputData()
	initialState := createInitialState(inputData)
	fmt.Println(solution(initialState))
}

import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Deque;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

public class Solution {

  private static int[] readInputData() {

    Scanner scanner = null;

    try {
      scanner = new Scanner(System.in);

      scanner.nextLine();

      final String[] disksLocationsStringArray = scanner.nextLine().split(" ");
      final int[] disksLocationsIntArray = Arrays.stream(disksLocationsStringArray).mapToInt(Integer::parseInt)
          .toArray();

      return disksLocationsIntArray;
    } finally {
      scanner.close();
    }
  }

  private static ArrayList<Stack<Integer>> transformInputData(int[] inputData) {

    final var result = new ArrayList<Stack<Integer>>(
        Arrays.asList(
            new Stack<Integer>(),
            new Stack<Integer>(),
            new Stack<Integer>(),
            new Stack<Integer>()));

    for (int i = inputData.length - 1; i >= 0; i--) {
      final int rod = inputData[i] - 1;
      final int disk = i;
      result.get(rod).push(disk);
    }

    return result;
  }

  private static void sortState(ArrayList<Stack<Integer>> state) {

    final var toSort = new ArrayList<Stack<Integer>>(
        Arrays.asList(
            state.get(1),
            state.get(2),
            state.get(3)));

    Collections.sort(toSort, new Comparator<Stack<Integer>>() {
      @Override
      public int compare(Stack<Integer> lhs, Stack<Integer> rhs) {
        final boolean lhsEmpty = lhs.empty();
        final boolean rhsEmpty = rhs.empty();

        if (lhsEmpty) {
          return rhsEmpty ? 0 : 1;
        }

        return rhsEmpty ? -1 : (rhs.peek() - lhs.peek());
      }
    });

    state.set(1, toSort.get(0));
    state.set(2, toSort.get(1));
    state.set(3, toSort.get(2));
  }

  private static int solution(ArrayList<Stack<Integer>> initialState) {

    final class Tuple<X, Y> {
      final X x;
      final Y y;

      Tuple(X x, Y y) {
        this.x = x;
        this.y = y;
      }
    }

    final Deque<Tuple<ArrayList<Stack<Integer>>, Integer>> stateDeque = new LinkedList<>();
    sortState(initialState);
    stateDeque.addLast(new Tuple<ArrayList<Stack<Integer>>, Integer>(initialState, 0));

    final HashSet<ArrayList<Stack<Integer>>> visitedStates = new HashSet<>();
    visitedStates.add(initialState);

    while (!stateDeque.isEmpty()) {
      final var currentTuple = stateDeque.removeFirst();
      final var currentState = currentTuple.x;
      final int currentStep = currentTuple.y;

      if (currentState.get(1).empty() && currentState.get(2).empty() && currentState.get(3).empty()) {
        return currentStep;
      }

      for (int i = 0; i < currentState.size(); i++) {
        for (int j = 0; j < currentState.size(); j++) {

          if (i == j) {
            continue;
          }

          final var toStack = currentState.get(i);
          final var fromStack = currentState.get(j);

          if (fromStack.empty()) {
            continue;
          }

          if (!toStack.empty() && (fromStack.peek() >= toStack.peek())) {
            continue;
          }

          final ArrayList<Stack<Integer>> newState = new ArrayList<Stack<Integer>>();
          for (final var currentStack : currentState) {
            final var newStack = new Stack<Integer>();
            newStack.addAll(currentStack);
            newState.add(newStack);
          }

          newState.get(i).push(newState.get(j).pop());
          sortState(newState);

          if (visitedStates.add(newState)) {
            stateDeque.addLast(new Tuple<ArrayList<Stack<Integer>>, Integer>(newState, currentStep + 1));
          }
        }
      }
    }

    return 0;
  }

  public static void main(String[] args) {
    final int[] inputData = readInputData();
    final var data = transformInputData(inputData);
    System.out.println(solution(data));
  }
}

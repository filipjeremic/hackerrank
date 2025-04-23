import java.util.HashSet;
import java.util.Hashtable;
import java.util.Scanner;

public class Solution {

    private static Hashtable<Integer, HashSet<Integer>> readInput() {
        Scanner scanner = new Scanner(System.in);

        scanner.nextInt();
        final int edgeCount = scanner.nextInt();

        final var m = new Hashtable<Integer, HashSet<Integer>>();

        for (int i = 0; i < edgeCount; i++) {
            final int nodeTo = scanner.nextInt();
            final int nodeFrom = scanner.nextInt();

            m.putIfAbsent(nodeFrom, new HashSet<Integer>());
            m.get(nodeFrom).add(nodeTo);
        }

        scanner.close();

        return m;
    }

    private static class Pair {
        private int childrenCount;
        private int result;

        private Pair(int childrenCount, int result) {
            this.childrenCount = childrenCount;
            this.result = result;
        }
    }

    private static Pair evenForest(final Hashtable<Integer, HashSet<Integer>> m, final int currentNode) {
        if (!m.containsKey(currentNode)) {
            return new Pair(1, 0);
        }

        int result = 0;
        int childrenCount = 0;

        for (final int childNode : m.get(currentNode)) {
            Pair childValues = evenForest(m, childNode);

            result += childValues.result;
            if (childValues.childrenCount % 2 == 0) {
                result++;
            } else {
                childrenCount += childValues.childrenCount;
            }
        }

        return new Pair(++childrenCount, result);
    }

    public static void main(String[] args) {
        final var m = readInput();
        Pair values = evenForest(m, 1);
        System.out.println(values.result);
    }
}

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class Solution {
    private static int[][] readData() {
        final Scanner scan = new Scanner(System.in);

        final int n = scan.nextInt();
        final int[][] data = new int[n][2];

        for (int i = 0; i < n; i++) {
            data[i][0] = scan.nextInt();
            data[i][1] = scan.nextInt();
        }

        scan.close();

        return data;
    }

    private static int[] getMinMax(final HashMap<Integer, LinkedList<Integer>> m) {
        int minSize = Integer.MAX_VALUE;
        int maxSize = Integer.MIN_VALUE;

        for (final LinkedList<Integer> l : m.values()) {
            final int currentSize = l.size();

            if (currentSize < minSize) {
                minSize = currentSize;
            }

            if (currentSize > maxSize) {
                maxSize = currentSize;
            }
        }

        return new int[] { minSize, maxSize };
    }

    private static int[] componentsInGraph(final int[][] data) {
        final HashMap<Integer, LinkedList<Integer>> m = new HashMap<>();

        for (final int[] pair : data) {
            final int a = pair[0];
            final int b = pair[1];

            final boolean hasA = m.containsKey(a);
            final boolean hasB = m.containsKey(b);

            if (!hasA && !hasB) {
                final var l = new LinkedList<>(List.of(a, b));

                m.put(a, l);
                m.put(b, l);

                continue;
            }

            final var listA = m.get(a);
            final var listB = m.get(b);

            if (hasA && hasB) {
                if (listA == listB) {
                    continue;
                }

                final int sizeA = listA.size();
                final int sizeB = listB.size();

                final LinkedList<Integer> listSmall = (sizeA < sizeB ? listA : listB);
                final LinkedList<Integer> listLarge = (sizeA >= sizeB ? listA : listB);

                for (final var i : listSmall) {
                    m.put(i, listLarge);
                    listLarge.add(i);
                }

                continue;
            }

            final int valueToInsert = (hasA ? b : a);
            final var insertList = (hasA ? listA : listB);

            insertList.add(valueToInsert);
            m.put(valueToInsert, insertList);
        }

        return getMinMax(m);
    }

    public static void main(String[] args) {
        final int[] result = componentsInGraph(readData());
        System.out.printf("%d %d\n", result[0], result[1]);
    }
}

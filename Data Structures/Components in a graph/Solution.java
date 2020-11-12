/*

Time complexity: O(n)
Space complexity: O(n)

The logic:
    - you need to keep track of which values are connected (the order is irrelevant)
    - this is done by having a map which says which value is in which list (lists are unique and shared)
    - when a new pair is examined there a X cases
        1) both values are new -> new list and map entries
        2) both values are not new and they are in the same list already -> do nothing
        3) both values are not new and they are not in the same list -> update the map entries for
            the values in one list to point to the other list and add the values from one list to the
            other list (looping through the smaller list because of performance)
        4) one value is new -> add it to the list of the other value and create the map entry for it

*/

import java.util.Scanner;
import java.util.HashMap;
import java.util.LinkedList;

public class Solution
{
    private static int[][] readData()
    {
        final Scanner scan = new Scanner(System.in);

        final int n = scan.nextInt();
        final int[][] gb = new int[n][2];

        for (int i = 0; i < n; i++)
        {
            gb[i][0] = scan.nextInt();
            gb[i][1] = scan.nextInt();
        }

        scan.close();

        return gb;
    }

    private static int[] getMinMaxListSize(final HashMap<Integer, LinkedList<Integer>> m)
    {
        int min = Integer.MAX_VALUE;
        int max = Integer.MIN_VALUE;

        for (final LinkedList<Integer> l: m.values())
        {
            final int size = l.size();
            if (size < min) min = size;
            if (size > max) max = size;
        }

        return new int[]{ min, max };
    }

    private static int[] componentsInGraph(final int[][] gb)
    {
        final HashMap<Integer, LinkedList<Integer>> m = new HashMap<>();

        for (int [] p: gb)
        {
            final int a = p[0];
            final int b = p[1];

            final boolean hasA = m.containsKey(a);
            final boolean hasB = m.containsKey(b);

            if (!hasA && !hasB)
            {
                final LinkedList<Integer> l = new LinkedList<>();
                l.add(a);
                l.add(b);

                m.put(a, l);
                m.put(b, l);

                continue;
            }

            final LinkedList<Integer> la = m.get(a);
            final LinkedList<Integer> lb = m.get(b);

            if (hasA && hasB)
            {
                if (la == lb) continue;

                final int sizeA = la.size();
                final int sizeB = lb.size();

                final LinkedList<Integer> listSmall = (sizeA < sizeB ? la : lb);
                final LinkedList<Integer> listLarge = (sizeA >= sizeB ? la : lb);

                listSmall.forEach(i ->
                    {
                        m.put(i, listLarge);
                        listLarge.add(i);
                    }
                );

                continue;
            }

            final int valueToInsert = (hasA ? b : a);
            final LinkedList<Integer> whereToInsert = (hasA ? la : lb);

            whereToInsert.add(valueToInsert);
            m.put(valueToInsert, whereToInsert);
        }

        return getMinMaxListSize(m);
    }

    public static void main(String[] args)
    {
        final int[] result = componentsInGraph(readData());
        System.out.println(result[0] + " " + result[1]);
    }
}

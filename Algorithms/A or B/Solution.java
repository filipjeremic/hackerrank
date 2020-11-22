/*

Time complexity: O(n)
Space complexity: O(n)

The logic:

The numbers in this problem are extremely large and are handled as strings.
The solution has two parts: mandatory and optimization.

Mandatory part - here we attempt to transform A and B so that A | B = C with
the minimum number of changes. For this we use a table which has every combination
of A, B and C. So for each value of A and B (both 0..15, that is 0x0..0xF), we store
how many changes are required and what are the resulting A and B to get A | B = C.
The size of this table is 16x16x16 = 4096. We do this once because we don’t want to
recalculate the same combinations. If this part fails, the numbers can’t be transformed
with up to K changes and we print out -1.

Optimization part - we use the remaining K to optimize. This part is simpler because
if a bit in C is 0 there is nothing to optimize (because in this case, after the mandatory part,
bit A and bit B are both 0, which is already optimal). When bit C is 1 there are 3 cases:

| bit A | bit B |
|   0   |   1   |
|   1   |   0   |
|   1   |   1   |

We always want bit A to be 0 since A has priority. Therefore, bit B needs to be 1.
In the first case, we already have those values and there is nothing to be done.
In the second case we need to change both bit A and bit B, so two steps are required.
In the third case all we need to do is set bit A to 0.
Notice that this loop doesn’t end at the first failure because you can have a situation
where K = 1 in case two. In this case you skip the transformation and continue checking
because there might be a case three later on to ultimately use the last K.

Important note - the output must be upper case to be accepted on HackerRank.

*/

import java.util.Scanner;

public class Solution
{
    private static int intBit(final int value, final int mask)
    {
        return ((value & mask) > 0) ? 1 : 0;
    }

    private static class Changes
    {
        public int count = 0;
        public int a = 0;
        public int b = 0;

        public Changes() {}

        public Changes(final int count, final int a, final int b)
        {
            this.count = count;
            this.a = a;
            this.b = b;
        }
    }

    private static Changes getMandatoryChanges(final int a, final int b, final int c)
    {
        int totalChangeCount = 0;
        int newA = 0;
        int newB = 0;

        for (int i = 8; i > 0; i >>>= 1)
        {
            final int aBit = intBit(a, i);
            final int bBit = intBit(b, i);
            final int cBit = intBit(c, i);

            final int changeCount = ((cBit ^ 1) * (aBit + bBit)) + (cBit * ((aBit | bBit) ^ 1));

            totalChangeCount += changeCount;
            newA = (newA << 1) | (cBit * aBit);
            newB = (newB << 1) | (cBit * (bBit + changeCount));
        }

        return new Changes(totalChangeCount, newA, newB);
    }

    private static Changes[][][] getMandatoryChangesTable()
    {
        final int n = 16;
        final Changes[][][] t = new Changes[16][16][16];

        for (int a = 0; a < n; a++)
        {
            for (int b = 0; b < n; b++)
            {
                for (int c = 0; c < n; c++)
                {
                    t[a][b][c] = getMandatoryChanges(a, b, c);
                }
            }
        }

        return t;
    }

    private static final Changes[][][] mandatoryChangesTable = getMandatoryChangesTable();

    private static int mandatoryChanges(int k, final char[] a, final char[] b, final char[] c)
    {
        final int size = a.length;

        for (int i = 0; i < size; i++)
        {
            final int intA = Character.getNumericValue(a[i]);
            final int intB = Character.getNumericValue(b[i]);
            final int intC = Character.getNumericValue(c[i]);

            Changes changes = mandatoryChangesTable[intA][intB][intC];

            k -= changes.count;
            if (k < 0) break;

            a[i] = Character.toUpperCase(Character.forDigit(changes.a, 16));
            b[i] = Character.toUpperCase(Character.forDigit(changes.b, 16));
        }

        return k;
    }

    private static Changes optimize(int k, final int a, final int b, final int c)
    {
        Changes changes = new Changes();

        for (int i = 8; i > 0; i >>>= 1)
        {
            final int aBit = intBit(a, i);
            final int bBit = intBit(b, i);
            final int cBit = intBit(c, i);
            final int changeCount = aBit + (bBit ^ 1);

            if ((cBit == 0) || (changeCount > k))
            {
                changes.a = (changes.a << 1) | aBit;
                changes.b = (changes.b << 1) | bBit;
            }
            else
            {
                k -= changeCount;
                changes.count += changeCount;
                changes.a = (changes.a << 1) | 0;
                changes.b = (changes.b << 1) | 1;
            }
        }

        return changes;
    }

    private static void optimizationChanges(int k, final char[] a, final char[] b, final char[] c)
    {
        for (int i = 0; i < a.length; i++)
        {
            if (k == 0) break;

            final int intA = Character.getNumericValue(a[i]);
            final int intB = Character.getNumericValue(b[i]);
            final int intC = Character.getNumericValue(c[i]);

            Changes changes = optimize(k, intA, intB, intC);

            k -= changes.count;

            a[i] = Character.toUpperCase(Character.forDigit(changes.a, 16));
            b[i] = Character.toUpperCase(Character.forDigit(changes.b, 16));
        }
    }

    private static void convertLeadingZeroesToSpaces(final char[] arr)
    {
        for (int i = 0; i < arr.length - 1; i++)
        {
            if (arr[i] != '0') break;
            arr[i] = ' ';
        }
    }

    private static void aOrB(int k, final char[] a, final char[] b, final char[] c)
    {
        k = mandatoryChanges(k, a, b, c);

        if (k < 0)
        {
            System.out.println(-1);
            return;
        }

        optimizationChanges(k, a, b, c);

        convertLeadingZeroesToSpaces(a);
        convertLeadingZeroesToSpaces(b);

        System.out.println(String.valueOf(a).trim());
        System.out.println(String.valueOf(b).trim());
    }

    public static void main(String[] args)
    {
        final Scanner scan = new Scanner(System.in);

        final int q = Integer.parseInt(scan.nextLine());

        for (int i = 0; i < q; i++)
        {
            final int k = Integer.parseInt(scan.nextLine());
            final char[] a = scan.nextLine().toCharArray();
            final char[] b = scan.nextLine().toCharArray();
            final char[] c = scan.nextLine().toCharArray();

            aOrB(k, a, b, c);
        }

        scan.close();
    }
}

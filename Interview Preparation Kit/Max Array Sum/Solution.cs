/*

Iterative solution

Time complexity: O(n)
Space complexity: O(1)

The logic:
    - every value that you use, the adjacent one you can't
    - therefore you have to skip everything that is not required
    - when you skip a value you get the maximum sum so far (this restarts the process of considering values)
    - negative values are not considered
    - for positive values you have to check what's larger, max_sum(i - 2) + value or max_sum(i - 1)
    - if max_sum(i - 2) + value is larger you consider the value (here you have to swap the sums because you added a value)
    - if max_sum(i - 1) is larger you don't consider value

*/

using System;

class Solution
{
    private static int maxSubsetSum(ref int[] arr)
    {
        var (appendable, notAppendable) = (0, 0);

        foreach (int x in arr)
        {
            if (x <= 0)
            {
                appendable = notAppendable = Math.Max(appendable, notAppendable);
                continue;
            }

            appendable += x;

            if (notAppendable >= appendable)
            {
                appendable = notAppendable;
                continue;
            }

            int temp = appendable;
            appendable = notAppendable;
            notAppendable = temp;
        }

        return Math.Max(appendable, notAppendable);
    }

    static void Main(string[] args)
    {
        Console.ReadLine();

        int[] arr = Array.ConvertAll(Console.ReadLine().Split(' '), arrTemp => Convert.ToInt32(arrTemp));

        Console.WriteLine(maxSubsetSum(ref arr));
    }
}

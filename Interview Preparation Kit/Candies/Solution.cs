// The logic:
//   - every child must get at least 1 piece of candy
//   - the amout of candy a child gets depends only on its neighbors
//   - if the childs rating is higher than that of its previous neighbor,
//         it gets 1 piece of candy more than the previous neighbor, otherwise it gets 1
//   - same rule applies for its next neighbor
//   - the child gets the greater (max) of the two values pieces of candy

// Iterative solution

// Time complexity: O(n)
// Space complexity: O(n)

using System;
using System.Linq;

class Solution
{
    static long candies(int[] ratings)
    {
        int n = ratings.Length;

        long[] candy = Enumerable.Repeat(1l, n).ToArray();

        for (int i = 1; i < n; i++)
        {
            if (ratings[i] > ratings[i - 1])
            {
                candy[i] = candy[i - 1] + 1;
            }
        }

        for (int i = n - 2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i + 1])
            {
                candy[i] = Math.Max(candy[i], candy[i + 1] + 1);
            }
        }

        return candy.Sum();
    }

    static void Main(string[] args)
    {
        int n = Convert.ToInt32(Console.ReadLine());
        int[] arr = new int [n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = Convert.ToInt32(Console.ReadLine());
        }

        Console.WriteLine(candies(arr));
    }
}

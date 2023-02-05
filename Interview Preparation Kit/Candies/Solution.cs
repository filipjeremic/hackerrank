using System;
using System.Linq;

class Solution
{
  static long candies(int[] ratings)
  {
    int n = ratings.Length;

    long[] candy = Enumerable.Repeat(1L, n).ToArray();

    for (int i = 1; i < n; i++)
    {
      if (ratings[i] > ratings[i - 1])
      {
        candy[i] = candy[i - 1] + 1;
      }
    }

    for (int i = n - 2; i >= 0; i--)
    {
      if ((ratings[i] > ratings[i + 1]) && (candy[i] < candy[i + 1] + 1))
      {
        candy[i] = candy[i + 1] + 1;
      }
    }

    return candy.Sum();
  }

  static void Main(string[] args)
  {
    int n = Convert.ToInt32(Console.ReadLine());
    int[] arr = new int[n];
    for (int i = 0; i < n; i++)
    {
      arr[i] = Convert.ToInt32(Console.ReadLine());
    }

    Console.WriteLine(candies(arr));
  }
}

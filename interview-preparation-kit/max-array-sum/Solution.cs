using System;

class Solution
{
  private static int maxSubsetSum(ref int[] arr)
  {
    var (sumWithCurrent, sumWithPrevious) = (0, 0);

    foreach (int x in arr)
    {
      if (x <= 0)
      {
        sumWithCurrent = sumWithPrevious = Math.Max(sumWithCurrent, sumWithPrevious);
        continue;
      }

      sumWithCurrent += x;

      if (sumWithPrevious >= sumWithCurrent)
      {
        sumWithCurrent = sumWithPrevious;
        continue;
      }

      int temp = sumWithCurrent;
      sumWithCurrent = sumWithPrevious;
      sumWithPrevious = temp;
    }

    return Math.Max(sumWithCurrent, sumWithPrevious);
  }

  static void Main(string[] args)
  {
    Console.ReadLine();

    int[] arr = Array.ConvertAll(Console.ReadLine().Split(' '), arrTemp => Convert.ToInt32(arrTemp));

    Console.WriteLine(maxSubsetSum(ref arr));
  }
}

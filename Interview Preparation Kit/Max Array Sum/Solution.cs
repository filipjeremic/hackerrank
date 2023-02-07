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

using System;

class Solution
{
  private static int getNextPow2(int n)
  {
    if (n == 0)
    {
      return 1;
    }

    int result = 1;

    while (result <= n)
    {
      result *= 2;
    }

    return result;
  }

  private static ulong[,] getInitialCarryMatrix(int lowValue, int highValue)
  {
    int N = getNextPow2(highValue);

    ulong[,] initialCarryMatrix = new ulong[lowValue + 1, N];

    for (int i = 1; i <= lowValue; i++)
    {
      for (int j = i; j <= highValue; j++)
      {
        initialCarryMatrix[i, i ^ j] = 1;
      }
    }

    return initialCarryMatrix;
  }

  private static void reduceMatrix(ulong[,] carryMatrix)
  {
    int rows = carryMatrix.GetLength(0);
    int cols = carryMatrix.GetLength(1);

    for (int i = rows - 1; i > 1; i--)
    {
      for (int j = 0; j < cols; j++)
      {
        carryMatrix[i - 1, j] += carryMatrix[i, j];
      }
    }
  }

  private static ulong[,] xorCarryMatrix(int B, ulong[,] carryMatrix)
  {
    int N = carryMatrix.GetLength(1);

    ulong[,] xorMatrix = new ulong[B + 1, N];

    for (int i = 1; i <= B; i++)
    {
      for (int j = 0; j < N; j++)
      {
        if (carryMatrix[i, j] == 0)
        {
          continue;
        }

        xorMatrix[i, i ^ j] = carryMatrix[i, j];
      }
    }

    return xorMatrix;
  }

  private static ulong calculateResult(int A, ulong[,] xorMatrix)
  {
    int N = xorMatrix.GetLength(1);

    ulong result = 0;

    for (int i = 1; i <= A; i++)
    {
      for (int j = 0; j < N; j++)
      {
        if (i != j)
        {
          result += xorMatrix[i, j];
        }
      }
    }

    return result;
  }

  static void Main(string[] args)
  {
    int[] values = Array.ConvertAll(Console.ReadLine().Split(' '), arrTemp => Convert.ToInt32(arrTemp));

    Array.Sort(values);

    var carryMatrix = getInitialCarryMatrix(values[2], values[3]);
    reduceMatrix(carryMatrix);

    carryMatrix = xorCarryMatrix(values[1], carryMatrix);
    reduceMatrix(carryMatrix);

    Console.WriteLine(calculateResult(values[0], carryMatrix));
  }
}

class Solution
{
  private static bool isOdd(int number)
  {
    return number % 2 != 0;
  }

  private static bool isPossible(int sr, int sc, int er, int ec)
  {
    if (isOdd(er + sr))
    {
      return false;
    }

    if (isOdd(ec + sc))
    {
      return (er - sr + 2) % 4 == 0;
    }

    return (er - sr) % 4 == 0;
  }

  private static void printShortestPath(int n, int sr, int sc, int er, int ec)
  {
    int moveCount = 0;
    System.Text.StringBuilder sb = new System.Text.StringBuilder();

    while (sr != er || sc != ec)
    {
      if (sr > er)
      {
        // moving up
        sb.Append('U');

        bool leftUpFirst = ((ec - sc) * 2) < (sr - er);
        if (sc > 0 && ((sc >= ec) || leftUpFirst))
        {
          sb.Append('L');
          sc--;
        }
        else
        {
          sb.Append('R');
          sc++;
        }
        sr -= 2;
      }
      else if (sr < er)
      {
        // moving down or right

        if ((ec - sc) * 2 > (er - sr))
        {
          // moving right
          sb.Append('R');
          sc += 2;
        }
        else
        {
          // moving down
          sb.Append('L');

          bool rightDownFirst = (sc - ec) * 2 < (er - sr);
          if ((sc < n - 1) && ((sc <= ec) || rightDownFirst))
          {
            sb.Append('R');
            sc++;
          }
          else
          {
            sb.Append('L');
            sc--;
          }

          sr += 2;
        }
      }
      else
      {
        if (ec < sc)
        {
          sb.Append('L');
          sc -= 2;
        }
        else
        {
          sb.Append('R');
          sc += 2;
        }
      }

      moveCount++;
      sb.Append(' ');
    }

    Console.WriteLine(moveCount);
    Console.WriteLine(sb);
  }

  private static void solve(int n, int sr, int sc, int er, int ec)
  {
    if (!isPossible(sr, sc, er, ec))
    {
      Console.WriteLine("Impossible");
      return;
    }

    printShortestPath(n, sr, sc, er, ec);
  }

  public static void Main(string[] args)
  {
    int n = Convert.ToInt32(Console.ReadLine());

    var coordinates = Console.ReadLine().TrimEnd().Split(' ').Select(int.Parse).ToArray();
    int sr = coordinates[0], sc = coordinates[1], er = coordinates[2], ec = coordinates[3];

    solve(n, sr, sc, er, ec);
  }
}

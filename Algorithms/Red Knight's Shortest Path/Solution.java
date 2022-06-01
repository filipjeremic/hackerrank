import java.util.Scanner;

public class Solution {

  private static boolean isOdd(final int number) {
    return number % 2 != 0;
  }

  private static boolean isPossible(final int sr, final int sc, final int er, final int ec) {
    if (isOdd(er + sr)) {
      return false;
    }

    if (isOdd(ec + sc)) {
      return (er - sr + 2) % 4 == 0;
    }

    return (er - sr) % 4 == 0;
  }

  private static void printShortestPath(final int n, int sr, int sc, final int er, final int ec) {
    int moveCount = 0;
    StringBuilder sb = new StringBuilder();

    while (sr != er || sc != ec) {
      if (sr > er) {
        // moving up
        sb.append('U');

        final boolean leftUpFirst = ((ec - sc) * 2) < (sr - er);
        if (sc > 0 && ((sc >= ec) || leftUpFirst)) {
          sb.append('L');
          sc--;
        } else {
          sb.append('R');
          sc++;
        }
        sr -= 2;
      } else if (sr < er) {
        // moving down or right

        if ((ec - sc) * 2 > (er - sr)) {
          // moving right
          sb.append('R');
          sc += 2;
        } else {
          // moving down
          sb.append('L');

          final boolean rightDownFirst = (sc - ec) * 2 < (er - sr);
          if ((sc < n - 1) && ((sc <= ec) || rightDownFirst)) {
            sb.append('R');
            sc++;
          } else {
            sb.append('L');
            sc--;
          }

          sr += 2;
        }
      } else {
        if (ec < sc) {
          sb.append('L');
          sc -= 2;
        } else {
          sb.append('R');
          sc += 2;
        }
      }

      moveCount++;
      sb.append(' ');
    }

    System.out.println(moveCount);
    System.out.println(sb);
  }

  private static void solve(final int n, final int sr, final int sc, final int er, final int ec) {
    if (!isPossible(sr, sc, er, ec)) {
      System.out.println("Impossible");
      return;
    }

    printShortestPath(n, sr, sc, er, ec);
  }

  public static void main(String[] args) {
    int n = 0, sr = 0, sc = 0, er = 0, ec = 0;

    Scanner scanner = new Scanner(System.in);

    n = scanner.nextInt();
    sr = scanner.nextInt();
    sc = scanner.nextInt();
    er = scanner.nextInt();
    ec = scanner.nextInt();

    scanner.close();

    solve(n, sr, sc, er, ec);
  }
}

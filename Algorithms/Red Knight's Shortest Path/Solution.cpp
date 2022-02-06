/*

Time complexity: O(n)
Space complexity: O(n) - because of the result string

The logic:

This problem is not too complex. Basically, one just needs to do the right
calculation to figure out whether or not it is possible to reach the
destination and if it is, align the conditions properly.

It is beneficial to understand that the red knight will never go back
vertically. So if he needs to go up, he will only go up or sideways. Same
thing for going down. Additionally, he can only stand on the green fields
that are marked (recursively). This shows us the positions which he can reach.
If the end position is on one of these fields, it is reachable, otherwise it
is "Impossible".

The tricky parts are the corner cases and priorities. Obviously, you can't go
over field bounds. But additionally you need to prioritize moves. For example
 - the moves from (6, 1) to (0, 2) are UL UR UR, not UR UL UR or UR UR UL,
 because UL has priority. So, even though the end position is to the right,
 you have to go to the left first. When going down, LR has priority over LL,
 but R has priority over LR. All this needs to be taken into consideration.
 When the red knight is in the row where the end is, the movement is trivial
 - just go left or right.

*/

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

constexpr bool isOdd(const int number) noexcept
{
  return number % 2 != 0;
}

constexpr bool isPossible(const int sr, const int sc, const int er, const int ec) noexcept
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

std::pair<int, std::string> printPath(const int n, int sr, int sc, const int er, const int ec)
{
  std::stringstream path;
  int moveCount = 0;

  while (sr != er || sc != ec)
  {
    if (sr > er)
    {
      // moving up
      path << 'U';

      const bool leftUpFirst = ((ec - sc) * 2) < (sr - er);
      if (sc > 0 && ((sc >= ec) || leftUpFirst))
      {
        path << 'L';
        sc--;
      }
      else
      {
        path << 'R';
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
        path << 'R';
        sc += 2;
      }
      else
      {
        // moving down
        path << 'L';

        const bool rightDownFirst = (sc - ec) * 2 < (er - sr);
        if ((sc < n - 1) && ((sc <= ec) || rightDownFirst))
        {
          path << 'R';
          sc++;
        }
        else
        {
          path << 'L';
          sc--;
        }

        sr += 2;
      }
    }
    else
    {
      if (ec < sc)
      {
        path << 'L';
        sc -= 2;
      }
      else
      {
        path << 'R';
        sc += 2;
      }
    }

    moveCount++;
    path << ' ';
  }

  return {moveCount, path.str()};
}

void solution(const int n, const int sr, const int sc, const int er, const int ec)
{
  if (!isPossible(sr, sc, er, ec))
  {
    std::cout << "Impossible" << std::endl;
    return;
  }

  auto result = printPath(n, sr, sc, er, ec);
  std::cout << result.first << '\n'
            << result.second << std::endl;
}

int main()
{
  int n = 0;
  int sr = 0;
  int sc = 0;
  int er = 0;
  int ec = 0;

  std::cin >> n >> sr >> sc >> er >> ec;

  solution(n, sr, sc, er, ec);

  return 0;
}

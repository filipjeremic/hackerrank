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

#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <vector>

uint64_t getNextPow2(const uint64_t n)
{
  if (n == 0)
  {
    return 1;
  }

  uint64_t result = 1;

  while (result <= n)
  {
    result *= 2;
  }

  return result;
}

auto getInitialCarryVector(const uint64_t small, const uint64_t large)
{
  const std::size_t N = getNextPow2(large);

  std::vector<std::vector<uint64_t>> carryVector(small + 1, std::vector<uint64_t>(N, 0));

  for (std::size_t i = 1; i <= small; i++)
  {
    for (std::size_t j = i; j <= large; j++)
    {
      carryVector[i][i ^ j] = 1;
    }
  }

  return carryVector;
}

void reduceVector(std::vector<std::vector<uint64_t>> &carryVector)
{
  const auto rows = carryVector.size();
  const auto cols = carryVector[0].size();

  for (std::size_t i = rows - 1; i > 1; i--)
  {
    for (std::size_t j = 0; j < cols; j++)
    {
      carryVector[i - 1][j] += carryVector[i][j];
    }
  }
}

auto xorCarryVector(const std::size_t B, const std::vector<std::vector<uint64_t>> &carryVector)
{
  const std::size_t N = carryVector[0].size();

  std::vector<std::vector<uint64_t>> xorVector(B + 1, std::vector<uint64_t>(N, 0));

  for (std::size_t i = 1; i <= B; i++)
  {
    for (std::size_t j = 0; j < N; j++)
    {
      if (carryVector[i][j] == 0)
      {
        continue;
      }

      xorVector[i][i ^ j] = carryVector[i][j];
    }
  }

  return xorVector;
}

uint64_t calculateResult(const std::size_t A, const std::vector<std::vector<uint64_t>> &xorVector)
{
  uint64_t result = 0;

  for (std::size_t i = 1; i <= A; i++)
  {
    result += std::accumulate(xorVector[i].cbegin(), xorVector[i].cend(), static_cast<uint64_t>(0));
    result -= xorVector[i][i];
  }

  return result;
}

int main()
{
  constexpr std::size_t VALUES_LEN = 4;

  std::array<int, VALUES_LEN> values;

  std::cin >> values[0] >> values[1] >> values[2] >> values[3];

  std::sort(std::begin(values), std::end(values));

  auto carryVector = getInitialCarryVector(values[2], values[3]);
  reduceVector(carryVector);

  carryVector = xorCarryVector(values[1], carryVector);
  reduceVector(carryVector);

  std::cout << calculateResult(values[0], carryVector) << std::endl;

  return 0;
}

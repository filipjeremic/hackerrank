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

auto getInitialCarryMatrix(const uint64_t lowValue, const uint64_t highValue)
{
  const std::size_t N = getNextPow2(highValue);

  std::vector<std::vector<uint64_t>> carryMatrix(lowValue + 1, std::vector<uint64_t>(N, 0));

  for (std::size_t i = 1; i <= lowValue; i++)
  {
    for (std::size_t j = i; j <= highValue; j++)
    {
      carryMatrix[i][i ^ j] = 1;
    }
  }

  return carryMatrix;
}

void reduceMatrix(std::vector<std::vector<uint64_t>> &carryMatrix)
{
  const auto rows = carryMatrix.size();
  const auto cols = carryMatrix[0].size();

  for (std::size_t i = rows - 1; i > 1; i--)
  {
    for (std::size_t j = 0; j < cols; j++)
    {
      carryMatrix[i - 1][j] += carryMatrix[i][j];
    }
  }
}

auto xorCarryMatrix(const std::size_t B, const std::vector<std::vector<uint64_t>> &carryMatrix)
{
  const std::size_t N = carryMatrix[0].size();

  std::vector<std::vector<uint64_t>> xorMatrix(B + 1, std::vector<uint64_t>(N, 0));

  for (std::size_t i = 1; i <= B; i++)
  {
    for (std::size_t j = 0; j < N; j++)
    {
      if (carryMatrix[i][j] == 0)
      {
        continue;
      }

      xorMatrix[i][i ^ j] = carryMatrix[i][j];
    }
  }

  return xorMatrix;
}

uint64_t calculateResult(const std::size_t A, const std::vector<std::vector<uint64_t>> &xorMatrix)
{
  uint64_t result = 0;

  for (std::size_t i = 1; i <= A; i++)
  {
    result += std::accumulate(xorMatrix[i].cbegin(), xorMatrix[i].cend(), static_cast<uint64_t>(0));
    result -= xorMatrix[i][i];
  }

  return result;
}

int main()
{
  constexpr std::size_t VALUES_LEN = 4;

  std::array<int, VALUES_LEN> values;

  std::cin >> values[0] >> values[1] >> values[2] >> values[3];

  std::sort(std::begin(values), std::end(values));

  auto carryMatrix = getInitialCarryMatrix(values[2], values[3]);
  reduceMatrix(carryMatrix);

  carryMatrix = xorCarryMatrix(values[1], carryMatrix);
  reduceMatrix(carryMatrix);

  std::cout << calculateResult(values[0], carryMatrix) << std::endl;

  return 0;
}

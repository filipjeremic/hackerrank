/*

D is the largest input number, C is the second largest.

Time complexity: O(C * D)
Space complexity: O(C * D)

Note: this algorithm can be written differently

The logic:

Dynamic programming solution. In essence, we keep XOR-ing and
transferring the result to the next input value. Since there
are only 4 input values I decided not to write a loop. In my
version there are 4 steps:

  1) sort the input values
  2) XOR values 3 and 4 to get the carry vector
  3) XOR the carry vector with values 2
  4) sum the carry vector values using values 1 to get the result

XOR is commutative, therefore we can sort the values. We want
to sort them to ensure uniqueness, and we do that by value <= nextValue.
E.g. if we have the values 2 and 3 our combinations are:

[1, 1] [1, 2] [1, 3] [2, 2] [2, 3]

[2, 1] is skipped since the second value can't be larger than the first.
([1, 2] and [2, 1] are the equivalent in this problem).

The carry vector contains the number of XOR values for each iteration
of each input value. An example should make it clearer:

  Lets say that the next input value is 3. The carry vector could look like this:
  
      0  1  2  3  4  5
  0 | 0  0  0  0  0  0
  1 | 1  2  0  1  3  0
  2 | 1  1  0  0  0  1
  3 | 0  1  0  1  0  0

This means that the value 1 will be XOR-ed with 0 once, 1 twice, 2 zero times,
3 once, 4 three times, 5 zero times. In the same way 2 will be XOR-ed with 0, 1
and 5 once and zero times with the rest. Same thing applies for the value 3.

After each XOR-ing comes the reduction. We do this because each iteration of
the next value takes all the carried values that are greater or equal that itself.
So if the next value is, say, 3, we would have:

  Iteration 1: takes values from 1, 2 and 3 (>= 1)
  Iteration 2: takes values from 2 and 3 (>= 2)
  Iteration 3: takes values from 3 (>=3)
  
This is how the values are accumulated.

In the end, getting the result is easy. After we have all the accumulated
values we only don’t consider the ones that XOR to 0, since we are collecting
everything that is not equal to 0. That means that we should sum everything
in every iteration except the index of the iteration (since A XOR A = 0).

*/

#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <vector>

auto getNextPow2(const unsigned int n)
{
  unsigned int result = 1;

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

#include <iostream>
#include <unordered_map>
#include <vector>

int maxSubsetSum(const std::vector<int> &arr) {
  std::unordered_map<int, int> memo;

  auto maxSubsetSum = [&memo, &arr](const int i, const auto &maxSubsetSum) {
    if (i < 0)
      return 0;
    if (memo.find(i) != memo.cend())
      return memo.at(i);

    const int x = arr[i];
    const int x1 = maxSubsetSum(i - 1, maxSubsetSum);

    if (x <= 0) {
      memo[i] = x1;
      return x1;
    }

    const int x2 = maxSubsetSum(i - 2, maxSubsetSum) + x;

    const int result = std::max(x1, x2);
    memo[i] = result;

    return result;
  };

  return maxSubsetSum(arr.size() - 1, maxSubsetSum);
}

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<int> arr(n);

  for (int i = 0; i < n; i++)
    std::cin >> arr[i];

  std::cout << maxSubsetSum(arr);

  return 0;
}

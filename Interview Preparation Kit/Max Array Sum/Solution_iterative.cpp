#include <algorithm>
#include <iostream>
#include <vector>

int maxSubsetSum(const std::vector<int> &arr) {
  int sumWithCurrent = 0;
  int sumWithPrevious = 0;

  std::for_each(
      arr.cbegin(), arr.cend(), [&sumWithCurrent, &sumWithPrevious](const int x) {
        if (x <= 0) {
          sumWithCurrent = sumWithPrevious = std::max(sumWithCurrent, sumWithPrevious);
          return;
        }

        sumWithCurrent += x;

        if (sumWithPrevious >= sumWithCurrent) {
          sumWithCurrent = sumWithPrevious;
          return;
        }

        std::swap(sumWithCurrent, sumWithPrevious);
      });

  return std::max(sumWithCurrent, sumWithPrevious);
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

#include <algorithm>
#include <iostream>
#include <vector>

int maxSubsetSum(const std::vector<int> &arr) {
  int appendable = 0;
  int notAppendable = 0;

  std::for_each(
      arr.cbegin(), arr.cend(), [&appendable, &notAppendable](const int x) {
        if (x <= 0) {
          appendable = notAppendable = std::max(appendable, notAppendable);
          return;
        }

        appendable += x;

        if (notAppendable >= appendable) {
          appendable = notAppendable;
          return;
        }

        std::swap(appendable, notAppendable);
      });

  return std::max(appendable, notAppendable);
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

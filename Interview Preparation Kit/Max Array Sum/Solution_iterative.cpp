/*

Iterative solution

Time complexity: O(n)
Space complexity: O(1)

The logic:
    - every value that you use, the adjacent one you can't
    - therefore you have to skip everything that is not required
    - when you skip a value you get the maximum sum so far (this restarts the process of considering values)
    - negative values are not considered
    - for positive values you have to check what's larger, max_sum(i - 2) + value or max_sum(i - 1)
    - if max_sum(i - 2) + value is larger you consider the value (here you have to swap the sums because you added a value)
    - if max_sum(i - 1) is larger you don't consider value

*/

#include <algorithm>
#include <iostream>
#include <vector>

int maxSubsetSum(const std::vector<int>& arr)
{
    int appendable = 0;
    int notAppendable = 0;

    std::for_each(arr.cbegin(), arr.cend(), [&appendable, &notAppendable](const int x)
    {
        if (x <= 0)
        {
            appendable = notAppendable = std::max(appendable, notAppendable);
            return;
        }

        appendable += x;

        if (notAppendable >= appendable)
        {
            appendable = notAppendable;
            return;
        }

        std::swap(appendable, notAppendable);
    });

    return std::max(appendable, notAppendable);
}

int main()
{
    int n = 0;
    std::cin >> n;

    std::vector<int> arr(n);

    for (int i = 0; i < n; i++) std::cin >> arr[i];

    std::cout << maxSubsetSum(arr);

    return 0;
}

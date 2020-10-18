#include <bits/stdc++.h>

/*

Note: this solution is similar to Solution_recursive_0.cpp. The goal was to remove the ugly
array bound checking. This is achieved by adding a "dummy" value on both sides of the initial array.

The logic:
    - every child must get at least 1 piece of candy
    - the amout of candy a child gets depends only on its neighbors
    - if the childs rating is higher than that of its previous neighbor,
        it gets 1 piece of candy more than the previous neighbor, otherwise it gets 1
    - same rule applies for its next neighbor
    - the child gets the greater (max) of the two values pieces of candy
    
Time complexity: O(n)
Space complexity: O(n)

*/

std::pair<long, int> candiesRecursive1(const std::vector<int> &arr, const size_t index, const int prevCandy)
{
    const auto n = arr.size();

    if (index == n - 1) return {0, 1};

    const int prevBound = (arr[index] > arr[index - 1]) ? prevCandy + 1 : 1;
    const auto next = candiesRecursive1(arr, index + 1, prevBound);
    const int nextBound = (arr[index] > arr[index + 1]) ? next.second + 1 : 1;
    const auto myCandyCount = std::max(prevBound, nextBound);
    return {next.first + myCandyCount, myCandyCount};
}

using namespace std;

// Complete the candies function below.
long candies(int n, vector<int> arr)
{
    return candiesRecursive1(arr, 1, 1).first;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    n += 2;

    vector<int> arr(n, 1);
    arr[0] = arr[n - 1] = 100000;

    for (int i = 1; i < n - 1; i++) {
        int arr_item;
        cin >> arr_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        arr[i] = arr_item;
    }

    long result = candies(n, arr);

    fout << result << "\n";

    fout.close();

    return 0;
}

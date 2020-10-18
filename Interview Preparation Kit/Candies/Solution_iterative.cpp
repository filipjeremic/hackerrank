/*

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

#include <bits/stdc++.h>

using namespace std;

// Complete the candies function below.
long candies(int n, vector<int> arr)
{
    vector<int> candy(n, 1);
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > arr[i - 1]) candy[i] = candy[i - 1] + 1;
    }

    // Careful with unsigned values here (i >= 0)
    // I intentionally used int in the loops since we know it is big enough
    for (int i = n - 2; i >= 0; i--)
    {
        if (arr[i] > arr[i + 1]) candy[i] = max(candy[i], candy[i + 1] + 1);
    }

    return std::accumulate(candy.cbegin(), candy.cend(), 0l);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
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

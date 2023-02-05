#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}

pair<long, int> candiesRecursive0(const vector<int> &arr, const size_t index, const int prevCandy)
{
    const auto n = arr.size();

    if (index == n)
    {
        return {0, 1};
    }

    const int prevBound = ((index > 0) && (arr[index] > arr[index - 1])) ? prevCandy + 1 : 1;
    const auto next = candiesRecursive0(arr, index + 1, prevBound);
    const int nextBound = ((index < n - 1) && (arr[index] > arr[index + 1])) ? next.second + 1 : 1;
    const auto myCandyCount = max(prevBound, nextBound);

    return {next.first + myCandyCount, myCandyCount};
}

long candies(int n, vector<int> arr)
{
    return candiesRecursive0(arr, 0, 1).first;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        string arr_item_temp;
        getline(cin, arr_item_temp);

        int arr_item = stoi(ltrim(rtrim(arr_item_temp)));

        arr[i] = arr_item;
    }

    long result = candies(n, arr);

    fout << result << "\n";

    fout.close();

    return 0;
}

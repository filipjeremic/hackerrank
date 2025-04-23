#include <iostream>
#include <unordered_map>

auto readInput() noexcept
{
    int edgeCount = 0;
    std::cin >> edgeCount >> edgeCount;

    std::unordered_multimap<int, int> m;

    for (int i = 0; i < edgeCount; i++)
    {
        int x = 0;
        int y = 0;

        std::cin >> x >> y;

        m.emplace(y, x);
    }

    return m;
}

std::pair<int, int> evenForest(const std::unordered_multimap<int, int> &m, int currentNode) noexcept
{
    if (m.count(currentNode) == 0)
    {
        return {1, 0};
    }

    int result = 0;
    int childrenCount = 0;

    const auto range = m.equal_range(currentNode);
    for (auto it = range.first; it != range.second; it++)
    {
        const auto [childChildrenCount, childResult] = evenForest(m, it->second);
        result += childResult;

        if (childChildrenCount % 2 == 0)
        {
            result++;
        }
        else
        {
            childrenCount += childChildrenCount;
        }
    }

    return {++childrenCount, result};
}

int main()
{
    const auto m = readInput();
    const auto result_pair = evenForest(m, 1);
    std::cout << result_pair.second << std::endl;

    return 0;
}

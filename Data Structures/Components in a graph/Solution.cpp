/*

Time complexity: O(n^2)
Space complexity: O(n)

The logic:
    - you need to keep track of which values are connected (the order is irrelevant)
    - this is done by having a map which says which value is in which list (lists are unique and shared)
    - when a new pair is examined there a X cases
        1) both values are new -> new list and map entries
        2) both values are not new and they are in the same list already -> do nothing
        3) both values are not new and they are not in the same list -> update the map entries for
            the values in one list to point to the other list and add the values from one list to the
            other list (I chose looping and modifying the smaller list because of performance)
        4) one value is new -> add it to the list of the other value and create the map entry for it

*/

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <list>
#include <memory>
#include <algorithm>

std::vector<std::pair<int, int>> readData()
{
    int n = 0;
    std::cin >> n;

    std::vector<std::pair<int, int>> data;
    data.reserve(n);

    for (int i = 0; i < n; i++)
    {
        int a = 0;
        int b = 0;
        std::cin >> a >> b;
        data.emplace_back(a, b);
    }

    return data;
}

auto getSize(const std::pair<int, std::shared_ptr<std::list<int>>>& e)
{
    return static_cast<int>(e.second->size());
}

std::pair<int, int> getMinMaxListSize(const std::unordered_map<int, std::shared_ptr<std::list<int>>>& m)
{
    int min = getSize(*m.cbegin());
    int max = min;

    std::for_each(m.cbegin(), m.cend(), [&min, &max](const auto& e)
    {
        const int size = getSize(e);
        if (size < min) min = size;
        if (size > max) max = size;
    });

    return { min, max };
}

std::pair<int, int> componentsInGraph(const std::vector<std::pair<int, int>> data)
{
    std::unordered_map<int, std::shared_ptr<std::list<int>>> m;

    std::for_each(data.cbegin(), data.cend(), [&m](const auto &p)
    {
        const int a = p.first;
        const int b = p.second;

        const auto itEnd = m.cend();

        const auto itA = m.find(a);
        const auto itB = m.find(b);

        const bool hasA = (itA != itEnd);
        const bool hasB = (itB != itEnd);

        if (!hasA && !hasB)
        {
            const auto listPtr = std::make_shared<std::list<int>>(std::initializer_list<int>{a, b});
            m.emplace(a, listPtr);
            m.emplace(b, listPtr);

            return;
        }

        if (hasA && hasB)
        {
            if (itA->second == itB->second) return;

            const auto sizeA = getSize(*itA);
            const auto sizeB = getSize(*itB);

            const auto& itSmall = (sizeA < sizeB) ? itA : itB;
            const auto& itLarge = (sizeA >= sizeB) ? itA : itB;

            const auto listSmallSharedPtr = itSmall->second;

            auto& listLarge = *itLarge->second;

            for (const auto i: *listSmallSharedPtr) m[i] = itLarge->second;

            listLarge.splice(listLarge.cbegin(), *listSmallSharedPtr);

            return;
        }

        const auto valueToInsert = (hasA ? b : a);
        const auto whereToInsert = (hasA ? itA->second : itB->second);

        whereToInsert->push_front(valueToInsert);
        m.emplace(valueToInsert, whereToInsert);
    });

    return getMinMaxListSize(m);
}

int main()
{
    const auto data = readData();

    const auto result = componentsInGraph(data);

    std::cout << result.first << ' ' << result.second << '\n';

    return 0;
}

#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

std::vector<std::pair<int, int>> readData() {
  std::size_t n = 0;
  std::cin >> n;

  std::vector<std::pair<int, int>> data(n);

  for (int i = 0; i < n; i++) {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;
    data[i] = {a, b};
  }

  return data;
}

std::pair<std::size_t, std::size_t> getMinMax(const std::unordered_map<int, std::shared_ptr<std::list<int>>> &m) {
  std::size_t minSize = m.cbegin()->second->size();
  std::size_t maxSize = minSize;

  for (const auto &[_, list] : m) {
    const std::size_t listSize = list->size();

    if (listSize < minSize) {
      minSize = listSize;
    }

    if (listSize > maxSize) {
      maxSize = listSize;
    }
  }

  return {minSize, maxSize};
}

std::pair<int, int> componentsInGraph(const std::vector<std::pair<int, int>> data) {
  std::unordered_map<int, std::shared_ptr<std::list<int>>> m;

  for (const auto [a, b] : data) {
    const auto iteratorA = m.find(a);
    const auto iteratorB = m.find(b);

    const bool hasA = (iteratorA != m.cend());
    const bool hasB = (iteratorB != m.cend());

    if (!hasA && !hasB) {
      const auto newListSP = std::make_shared<std::list<int>>(std::initializer_list<int>{a, b});
      m.emplace(a, newListSP);
      m.emplace(b, newListSP);
      continue;
    }

    if (hasA && hasB) {
      if (iteratorA->second == iteratorB->second) {
        continue;
      }

      const auto sizeA = iteratorA->second->size();
      const auto sizeB = iteratorB->second->size();

      const auto &iteratorSmall = (sizeA < sizeB) ? iteratorA : iteratorB;
      const auto &iteratorLarge = (sizeA >= sizeB) ? iteratorA : iteratorB;

      const auto smallListSP = iteratorSmall->second;

      auto &largeList = *iteratorLarge->second;

      for (const auto i : *smallListSP) {
        m[i] = iteratorLarge->second;
      }

      largeList.splice(largeList.cbegin(), *smallListSP);

      continue;
    }

    const auto valueToInsert = (hasA ? b : a);
    const auto insertLocation = (hasA ? iteratorA->second : iteratorB->second);
    insertLocation->push_front(valueToInsert);
    m.emplace(valueToInsert, insertLocation);
  }

  return getMinMax(m);
}

int main() {
  const auto data = readData();
  const auto result = componentsInGraph(data);
  std::cout << result.first << ' ' << result.second << '\n';

  return 0;
}

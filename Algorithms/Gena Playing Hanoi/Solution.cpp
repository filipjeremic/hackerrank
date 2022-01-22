#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <unordered_set>
#include <vector>

using State = std::vector<std::vector<int>>;

auto readInput()
{
  int size = 0;
  std::cin >> size;

  State data(4);
  std::for_each(data.begin(), data.end(),
                [size](auto& v)
                {
                  v.reserve(size);
                });

  std::vector<int> temp(size);
  for (int i = 0; i < size; i++)
  {
    std::cin >> temp[i];
  }

  for (int i = size; i > 0; i--)
  {
    data[temp[i - 1] - 1].push_back(i);
  }

  return data;
}

auto pow10(const unsigned int e) noexcept
{
  uint64_t result = 1;
  for (unsigned int i = 0; i < e; i++)
  {
    result *= 10;
  }

  return result;
}

template <>
struct std::hash<State>
{
  auto operator()(const State& state) const
  {
    std::size_t hash = 0;

    for (std::size_t i = 0; i < state.size(); i++)
    {
      for (const auto e : state[i])
      {
        hash += i * pow10(e - 1);
      }
    }

    return hash;
  }
};

auto getNextValidStates(const State& state)
{
  std::vector<State> result;

  for (std::size_t srcInd = 0; srcInd < state.size(); srcInd++)
  {
    if (state[srcInd].empty())
    {
      continue;
    }

    for (std::size_t dstInd = 0; dstInd < state.size(); dstInd++)
    {

      const auto srcTopValue = *(state[srcInd].rbegin());

      if (state[dstInd].empty() || (*(state[dstInd].rbegin()) > srcTopValue))
      {
        State stateCopy(state);

        stateCopy[srcInd].pop_back();
        stateCopy[dstInd].push_back(srcTopValue);

        std::sort(stateCopy.begin() + 1, stateCopy.end(),
                  [](const auto& s1, const auto& s2)
                  {
                    const bool s1Empty = s1.empty();
                    const bool s2Empty = s2.empty();

                    if (s1Empty)
                    {
                      return true;
                    }

                    if (s2Empty)
                    {
                      return s1Empty;
                    }

                    return *(s1.crbegin()) < *(s2.crbegin());
                  });

        result.emplace_back(std::move(stateCopy));
      }
    }
  }

  return result;
}

int getMinimumMoveCount(State startState)
{
  std::unordered_set<std::size_t> visitedStates({std::hash<State>{}(startState)});
  std::deque<std::pair<int, State>> remainingStates({{0, std::move(startState)}});

  while (!remainingStates.empty())
  {
    const auto currentElement(std::move(remainingStates.front()));
    const auto currentDepth = currentElement.first;
    const auto& currentState = currentElement.second;
    const auto currentStateHash = std::hash<State>{}(currentElement.second);
    remainingStates.pop_front();

    if (currentStateHash == 0)
    {
      return currentDepth;
    }

    std::vector<State> nextValidStates(getNextValidStates(currentState));
    std::for_each(nextValidStates.begin(), nextValidStates.end(),
                  [&remainingStates, &visitedStates, currentDepth](auto& nextValidState)
                  {
                    const auto nextValidStateHash = std::hash<State>{}(nextValidState);
                    if (visitedStates.find(nextValidStateHash) != visitedStates.cend())
                    {
                      return;
                    }

                    visitedStates.emplace(nextValidStateHash);
                    remainingStates.emplace_back(currentDepth + 1, std::move(nextValidState));
                  });
  }

  return -1;
}

int main()
{
  std::cout << getMinimumMoveCount(readInput());
  return 0;
}


#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct Changes {
  int m_count = 0;
  int m_a = 0;
  int m_b = 0;

  Changes(const int count, const int a, const int b) : m_count(count), m_a(a), m_b(b) {
  }
};

static inline int intBit(const int value, const int mask) {
  return ((value & mask) > 0) ? 1 : 0;
}

static Changes getMandatoryChanges(const int a, const int b, const int c) {
  int totalChangeCount = 0;
  int newA = 0;
  int newB = 0;

  for (int i = 8; i > 0; i >>= 1) {
    const int aBit = intBit(a, i);
    const int bBit = intBit(b, i);
    const int cBit = intBit(c, i);

    const int changeCount = ((cBit ^ 1) * (aBit + bBit)) + (cBit * ((aBit | bBit) ^ 1));

    totalChangeCount += changeCount;
    newA = (newA << 1) | (cBit * aBit);
    newB = (newB << 1) | (cBit * (bBit + changeCount));
  }

  return {totalChangeCount, newA, newB};
}

static auto getMandatoryChangesTable() {
  constexpr size_t N = 16;

  std::vector<std::vector<std::vector<Changes>>> tableA;

  for (size_t a = 0; a < N; a++) {
    std::vector<std::vector<Changes>> tableB;

    for (size_t b = 0; b < N; b++) {
      std::vector<Changes> tableC;

      for (size_t c = 0; c < N; c++) {
        tableC.push_back(getMandatoryChanges(a, b, c));
      }

      tableB.push_back(tableC);
    }

    tableA.push_back(tableB);
  }

  return tableA;
}

static const auto mandatoryChangesTable = getMandatoryChangesTable();

static int mandatoryChanges(int k, std::vector<int> &a, std::vector<int> &b, const std::vector<int> &c) {
  const auto size = a.size();

  for (size_t i = 0; i < size; i++) {
    const auto changes = mandatoryChangesTable[a[i]][b[i]][c[i]];

    k -= changes.m_count;
    if (k < 0)
      break;

    a[i] = changes.m_a;
    b[i] = changes.m_b;
  }

  return k;
}

static Changes optimize(int k, const int a, const int b, const int c) {
  int changeCountTotal = 0;
  int newA = 0;
  int newB = 0;

  for (int i = 8; i > 0; i >>= 1) {
    const int aBit = intBit(a, i);
    const int bBit = intBit(b, i);
    const int cBit = intBit(c, i);
    const int changeCount = aBit + (bBit ^ 1);

    const bool hasChanges = ((cBit == 1) && (changeCount <= k));

    newA = (newA << 1) | (hasChanges ? 0 : aBit);
    newB = (newB << 1) | (hasChanges ? 1 : bBit);

    if (hasChanges) {
      k -= changeCount;
      changeCountTotal += changeCount;
    }
  }

  return {changeCountTotal, newA, newB};
}

static void optimizationChanges(int k, std::vector<int> &a, std::vector<int> &b, const std::vector<int> &c) {
  for (size_t i = 0; i < a.size(); i++) {
    if (k == 0)
      break;

    auto changes = optimize(k, a[i], b[i], c[i]);

    k -= changes.m_count;

    a[i] = changes.m_a;
    b[i] = changes.m_b;
  }
}

static void aOrB(int k, const std::string &a, const std::string &b, const std::string &c) {
  const size_t size = a.size();

  auto stringToIntVector = [](const std::string &s, std::vector<int> &v) {
    std::transform(std::cbegin(s), std::cend(s), std::begin(v),
                   [](const char c) -> int { return ((c >= 'A') && (c <= 'Z')) ? (c - 'A' + 10) : (c - '0'); });
  };

  std::vector<int> vectorA(size, 0);
  std::vector<int> vectorB(size, 0);
  std::vector<int> vectorC(size, 0);

  stringToIntVector(a, vectorA);
  stringToIntVector(b, vectorB);
  stringToIntVector(c, vectorC);

  k = mandatoryChanges(k, vectorA, vectorB, vectorC);

  if (k < 0) {
    std::cout << "-1\n";
    return;
  }

  optimizationChanges(k, vectorA, vectorB, vectorC);

  auto print = [](const std::vector<int> &v) {
    bool skipZero = true;

    std::stringstream ss;

    for (const int i : v) {
      if ((i == 0) && skipZero)
        continue;
      skipZero = false;
      ss << static_cast<char>((i < 10) ? ('0' + i) : ('A' - 10 + i));
    }

    if (skipZero)
      ss << '0';

    std::cout << ss.str() << '\n';
  };

  print(vectorA);
  print(vectorB);
}

int main() {
  int q = 0;
  std::cin >> q;

  for (int i = 0; i < q; i++) {
    int k = 0;
    std::string a, b, c;

    std::cin >> k >> a >> b >> c;

    aOrB(k, a, b, c);
  }

  return 0;
}

/*

Time complexity: O(n)
Space complexity: O(n)

The logic:

The numbers in this problem are extremely large and are handled as strings.
The solution has two parts: mandatory and optimization.

Mandatory part - here we attempt to transform A and B so that A | B = C with
the minimum number of changes. For this we use a table which has every combination
of A, B and C. So for each value of A and B (both 0..15, that is 0x0..0xF), we store
how many changes are required and what are the resulting A and B to get A | B = C.
The size of this table is 16x16x16 = 4096. We do this once because we don’t want to
recalculate the same combinations. If this part fails, the numbers can’t be transformed
with up to K changes and we print out -1.

Optimization part - we use the remaining K to optimize. This part is simpler because
if a bit in C is 0 there is nothing to optimize (because in this case, after the mandatory part,
bit A and bit B are both 0, which is already optimal). When bit C is 1 there are 3 cases:

| bit A | bit B |
|   0   |   1   |
|   1   |   0   |
|   1   |   1   |

We always want bit A to be 0 since A has priority. Therefore, bit B needs to be 1.
In the first case, we already have those values and there is nothing to be done.
In the second case we need to change both bit A and bit B, so two steps are required.
In the third case all we need to do is set bit A to 0.
Notice that this loop doesn’t end at the first failure because you can have a situation
where K = 1 in case two. In this case you skip the transformation and continue checking
because there might be a case three later on to ultimately use the last K.

Important note - the output must be upper case to be accepted on HackerRank.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

struct Changes
{
    int m_count = 0;
    int m_a = 0;
    int m_b = 0;

    Changes(const int count, const int a, const int b) : m_count(count), m_a(a), m_b(b) {}
};

static inline int intBit(const int value, const int mask)
{
    return ((value & mask) > 0) ? 1 : 0;
}

static Changes getMandatoryChanges(const int a, const int b, const int c)
{
    int totalChangeCount = 0;
    int newA = 0;
    int newB = 0;

    for (int i = 8; i > 0; i >>= 1)
    {
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

static auto getMandatoryChangesTable()
{
    constexpr size_t N = 16;

    std::vector<std::vector<std::vector<Changes>>> tableA;

    for (size_t a = 0; a < N; a++)
    {
        std::vector<std::vector<Changes>> tableB;

        for (size_t b = 0; b < N; b++)
        {
            std::vector<Changes> tableC;

            for (size_t c = 0; c < N; c++)
            {
                tableC.push_back(getMandatoryChanges(a, b, c));
            }

            tableB.push_back(tableC);
        }

        tableA.push_back(tableB);
    }

    return tableA;
}

static const auto mandatoryChangesTable = getMandatoryChangesTable();

static int mandatoryChanges(int k, std::vector<int>& a, std::vector<int>& b, const std::vector<int>& c)
{
    const auto size = a.size();

    for (size_t i = 0; i < size; i++)
    {
        const auto changes = mandatoryChangesTable[a[i]][b[i]][c[i]];

        k -= changes.m_count;
        if (k < 0) break;

        a[i] = changes.m_a;
        b[i] = changes.m_b;
    }

    return k;
}

static Changes optimize(int k, const int a, const int b, const int c)
{
    int changeCountTotal = 0;
    int newA = 0;
    int newB = 0;

    for (int i = 8; i > 0; i >>= 1)
    {
        const int aBit = intBit(a, i);
        const int bBit = intBit(b, i);
        const int cBit = intBit(c, i);
        const int changeCount = aBit + (bBit ^ 1);

        const bool hasChanges = ((cBit == 1) && (changeCount <= k));

        newA = (newA << 1) | (hasChanges ? 0 : aBit);
        newB = (newB << 1) | (hasChanges ? 1 : bBit);

        if (hasChanges)
        {
            k -= changeCount;
            changeCountTotal += changeCount;
        }
    }

    return { changeCountTotal, newA, newB };
}

static void optimizationChanges(int k, std::vector<int>& a, std::vector<int>& b, const std::vector<int>& c)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        if (k == 0) break;

        auto changes = optimize(k, a[i], b[i], c[i]);

        k -= changes.m_count;

        a[i] = changes.m_a;
        b[i] = changes.m_b;
    }
}

static void aOrB(int k, const std::string& a, const std::string& b, const std::string& c)
{
    const size_t size = a.size();

    auto stringToIntVector = [](const std::string& s, std::vector<int>& v)
    {
        std::transform(std::cbegin(s), std::cend(s), std::begin(v), [](const char c) -> int
        {
            return ((c >= 'A') && (c <= 'Z')) ? (c - 'A' + 10) : (c - '0');
        });
    };

    std::vector<int> vectorA(size, 0);
    std::vector<int> vectorB(size, 0);
    std::vector<int> vectorC(size, 0);

    stringToIntVector(a, vectorA);
    stringToIntVector(b, vectorB);
    stringToIntVector(c, vectorC);

    k = mandatoryChanges(k, vectorA, vectorB, vectorC);

    if (k < 0)
    {
        std::cout << "-1\n";
        return;
    }

    optimizationChanges(k, vectorA, vectorB, vectorC);

    auto print = [](const std::vector<int>& v)
    {
        bool skipZero = true;

        std::stringstream ss;

        for (const int i: v)
        {
            if ((i == 0) && skipZero) continue;
            skipZero = false;
            ss << static_cast<char>((i < 10) ? ('0' + i) : ('A' - 10 + i));
        }

        if (skipZero) ss << '0';

        std::cout << ss.str() << '\n';
    };

    print(vectorA);
    print(vectorB);
}

int main()
{
    int q = 0;
    std::cin >> q;

    for (int i = 0; i < q; i++)
    {
        int k = 0;
        std::string a, b, c;

        std::cin >> k >> a >> b >> c;

        aOrB(k, a, b, c);
    }

    return 0;
}

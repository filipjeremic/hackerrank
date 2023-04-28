Time complexity: O(n)
Space complexity: O(n)

The logic:

The solution has two parts:
  - find A' and B' that satisfy the A' | B' = C equation
  - minimize A' and then B'

In the first part we attempt to transform A and B to A' and B' so that A' | B' = C.
We are changing the minimum number of bits required. To speed things up we use a static
table which has every combination of A, B and the resulting C. The table contains, for
each value of A and B (range 0..15, or in hex 0x0..0xF), how many bits need to change
and what the resulting A' and B' are so that A' | B' = C. The size of this table is
16x16x16 = 4096 and we populate it at the beginning. If this first part fails, the
numbers can’t be transformed with up to K changes and we print out -1.

In the second part we use the unused K changes to minimize first A' and then B'. Since
A' has priority the A' bit will always tend to be 0. There are 4 different cases:

| bit A'| bit B'| bit C |
|   0   |   0   |   0   |  already optimal => 0 changes
|   0   |   1   |   1   |  already optimal => 0 changes
|   1   |   0   |   1   |  we need to change bit A to 0 and bit B to 1 => 2 changes
|   1   |   1   |   1   |  change bit A to 0 => 1 change

The algorithm ends when either K is 0 or both A and B have been completely optimized.

The numbers in this problem are extremely large and are handled as strings.

Important note - HackerRank expects uppercase hexadecimal characters.

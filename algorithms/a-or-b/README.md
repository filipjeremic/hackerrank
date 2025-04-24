## The logic:

The problem is solved in two steps:
1. Finding A' and B' so that A' | B' = C
2. Minimizing only A'

---

### Step 1.

We attempt to transform A and B into A' and B' so that A' | B' = C with the minimal number of changes. Reaching this state is necessary in order to know if there is a solution. Afterwards we can minimize.

Legend:
- A: starting A
- B: starting B
- C: starting C
- A': goal A
- B': goal B
- dk: number of bits changed

| A | B | C | A' | B' | dk |
|---|---|---|----|----|----|
| 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 1 | 0 | 1 | 1 |
| 0 | 1 | 0 | 0 | 0 | 1 |
| 0 | 1 | 1 | 0 | 1 | 0 |
| 1 | 0 | 0 | 0 | 0 | 1 |
| 1 | 0 | 1 | 1 | 0 | 0 |
| 1 | 1 | 0 | 0 | 0 | 2 |
| 1 | 1 | 1 | 1 | 1 | 0 |

From this table we can create formulas for A', B' and dk:
- A' = A && C
- B' = C && (!A || (A && B))
- dk = number of bits changed (0, 1, or 2)

For each combination of bits we subtract dk from k, and if k >= 0 after going through all the bits we know there is a solution. If k goes below 0 (we don't have enough moves), there is no solution and we print -1.

---

### Step 2

We use the remaining k for optimization, to minimize A'.

After eliminating duplicates from the table above, the new table looks like this:

| A' | B' | C |
|----|----|---|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

Minimizing A' has priority over B' so we only consider the last 2 rows:

| A' | B' | C | A'' | B'' | dk |
|----|----|---|-----|-----|----|
| 1 | 0 | 1 | 0 | 1 | 2 |
| 1 | 1 | 1 | 0 | 1 | 1 |

What is different in this step is that no changes need to happen. There will still be a solution, it will just not be minimal.

Additionally, there is no need for a third step to minimize B'. Minimizing A' makes B' final, because in that situation A' will be 0 and B' will simply be equal to C.

---

### Complexity

Time: O(n)
Space: O(n)

---

### Notes

Input hexadecimal letters are always uppercase and the output needs to be uppercase as well.

Do not print leading zeroes in the solution.

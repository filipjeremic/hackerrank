Iterative solution

Time complexity: O(n)
Space complexity: O(1)

The logic:
  - every value that you use, the adjacent one you can't
  - therefore you have to skip everything that is not required
  - when you skip a value you get the maximum sum so far (this restarts the process of considering values)
  - negative values are not considered
  - for positive values you have to check what's larger, max_sum(i - 2) + value or max_sum(i - 1)
  - if max_sum(i - 2) + value is larger you consider the value (here you have to swap the sums because you added a value)
  - if max_sum(i - 1) is larger you don't consider value

---

Recursive solution

Time complexity: O(n)
Space complexity: O(n)

The logic:
  - for every value x at index i calculate the max sum [0..i-1]
  - if x is less than/equal to zero, the max sum is in [0..i-1]
  - otherwise it is the greater of [0..i-1] and [0..i-2] + x
  - memo is used to avoid recalculations

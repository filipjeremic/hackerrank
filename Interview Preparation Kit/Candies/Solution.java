// The logic:
//   - every child must get at least 1 piece of candy
//   - the amout of candy a child gets depends only on its neighbors
//   - if the childs rating is higher than that of its previous neighbor,
//         it gets 1 piece of candy more than the previous neighbor, otherwise it gets 1
//   - same rule applies for its next neighbor
//   - the child gets the greater (max) of the two values pieces of candy

// Iterative solution

// Time complexity: O(n)
// Space complexity: O(n)

import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.LongStream;
import java.lang.Math;

public class Solution {
    static long candies(int[] ratings) {
        final int n = ratings.length;

        final long[] candy = new long[n];
        Arrays.fill(candy, 1);

        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candy[i] = candy[i - 1] + 1;
            }
        }

        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candy[i] = Math.max(candy[i], candy[i + 1] + 1);
            }
        }

        return LongStream.of(candy).sum();
    }

    public static void main(String[] args) {
        final Scanner scanner = new Scanner(System.in);

        final int n = scanner.nextInt();
        final int[] arr = new int[n];
        for (int i = 0; i < n; i++)
            arr[i] = scanner.nextInt();
        scanner.close();

        System.out.println(candies(arr));
    }
}

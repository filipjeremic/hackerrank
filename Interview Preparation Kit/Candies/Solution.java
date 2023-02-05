import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.LongStream;

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
            if ((ratings[i] > ratings[i + 1]) && (candy[i] < (candy[i + 1] + 1))) {
                candy[i] = candy[i + 1] + 1;
            }
        }

        return LongStream.of(candy).sum();
    }

    public static void main(String[] args) {
        final Scanner scanner = new Scanner(System.in);

        final int n = scanner.nextInt();
        final int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }

        scanner.close();

        System.out.println(candies(arr));
    }
}

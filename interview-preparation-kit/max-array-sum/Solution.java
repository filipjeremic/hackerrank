import java.util.Arrays;
import java.util.Scanner;

// Note: a recursive solution won't work here (stack overflow)

public class Solution {

    private static int maxSubsetSum(final int[] arr) {
        int sumWithCurrent = 0;
        int sumWithPrevious = 0;

        for (final int x : arr) {
            if (x <= 0) {
                sumWithCurrent = sumWithPrevious = Math.max(sumWithCurrent, sumWithPrevious);
                continue;
            }

            sumWithCurrent += x;

            if (sumWithPrevious >= sumWithCurrent) {
                sumWithCurrent = sumWithPrevious;
                continue;
            }

            final int temp = sumWithCurrent;
            sumWithCurrent = sumWithPrevious;
            sumWithPrevious = temp;
        }

        return Math.max(sumWithCurrent, sumWithPrevious);
    }

    public static void main(String[] args) {
        final Scanner scanner = new Scanner(System.in);
        scanner.nextLine();
        final int[] arr = Arrays.stream(scanner.nextLine().trim().split(" ")).mapToInt(Integer::parseInt).toArray();
        scanner.close();

        System.out.println(maxSubsetSum(arr));
    }
}

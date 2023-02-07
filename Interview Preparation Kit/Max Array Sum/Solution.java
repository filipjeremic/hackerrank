import java.util.Arrays;
import java.util.Scanner;

// Note: a recursive solution won't work here (stack overflow)

public class Solution {

    private static int maxSubsetSum(final int[] arr) {
        int appendable = 0;
        int notAppendable = 0;

        for (final int x : arr) {
            if (x <= 0) {
                appendable = notAppendable = Math.max(appendable, notAppendable);
                continue;
            }

            appendable += x;

            if (notAppendable >= appendable) {
                appendable = notAppendable;
                continue;
            }

            final int temp = appendable;
            appendable = notAppendable;
            notAppendable = temp;
        }

        return Math.max(appendable, notAppendable);
    }

    public static void main(String[] args) {
        final Scanner scanner = new Scanner(System.in);
        scanner.nextLine();
        final int[] arr = Arrays.stream(scanner.nextLine().trim().split(" ")).mapToInt(Integer::parseInt).toArray();
        scanner.close();

        System.out.println(maxSubsetSum(arr));
    }
}

import java.util.Arrays;
import java.util.Scanner;

public class Solution {

  private static int getNextPow2(final int n) {
    int result = 1;

    while (result <= n) {
      result *= 2;
    }

    return result;
  }

  private static long[][] getInitialCarryMatrix(final int lowValue, final int highValue) {
    final int N = getNextPow2(highValue);

    final var carryMatrix = new long[lowValue + 1][N];

    for (int i = 1; i <= lowValue; i++) {
      for (int j = i; j <= highValue; j++) {
        carryMatrix[i][i ^ j] = 1;
      }
    }

    return carryMatrix;
  }

  private static void reduceMatrix(long[][] carryMatrix) {
    final var rows = carryMatrix.length;
    final var cols = carryMatrix[0].length;

    for (int i = rows - 1; i > 1; i--) {
      for (int j = 0; j < cols; j++) {
        carryMatrix[i - 1][j] += carryMatrix[i][j];
      }
    }
  }

  private static long[][] xorCarryMatrix(final int B, final long[][] carryMatrix) {
    final var N = carryMatrix[0].length;

    var xorMatrix = new long[B + 1][N];

    for (int i = 1; i <= B; i++) {
      for (int j = 0; j < N; j++) {
        xorMatrix[i][i ^ j] = carryMatrix[i][j];
      }
    }

    return xorMatrix;
  }

  private static long calculateResult(final int A, final long[][] xorMatrix) {
    long result = 0;

    for (int i = 1; i <= A; i++) {
      result += Arrays.stream(xorMatrix[i]).sum();
      result -= xorMatrix[i][i];
    }

    return result;
  }

  public static void main(String[] args) {
    int[] values = { 0, 0, 0, 0 };

    Scanner scanner = new Scanner(System.in);

    for (int i = 0; i < values.length; i++) {
      values[i] = scanner.nextInt();
    }

    scanner.close();

    Arrays.sort(values);

    var carryMatrix = getInitialCarryMatrix(values[2], values[3]);
    reduceMatrix(carryMatrix);

    carryMatrix = xorCarryMatrix(values[1], carryMatrix);
    reduceMatrix(carryMatrix);

    System.out.println(calculateResult(values[0], carryMatrix));
  }
}

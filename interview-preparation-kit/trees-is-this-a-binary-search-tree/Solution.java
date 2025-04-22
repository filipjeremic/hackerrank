import java.util.Arrays;
import java.util.Scanner;

public class Solution {

  static class Node {
    int data;
    Node left;
    Node right;

    Node(int _data, Node _left, Node _right) {
      data = _data;
      left = _left;
      right = _right;
    }
  }

  static boolean checkBST(final Node node, final int min, final int max) {

    if (node == null) {
      return true;
    }

    return (node.data > min &&
        node.data < max &&
        checkBST(node.left, min, node.data) &&
        checkBST(node.right, node.data, max));
  }

  static boolean checkBST(final Node root) {
    return checkBST(root, Integer.MIN_VALUE, Integer.MAX_VALUE);
  }

  static Node formTree(int[] data, int startIndex, int endIndex) {
    if (startIndex == endIndex) {
      return null;
    }

    int middleIndex = startIndex + (endIndex - startIndex) / 2;

    return new Node(
        data[middleIndex],
        formTree(data, startIndex, middleIndex),
        formTree(data, middleIndex + 1, endIndex));
  }

  public static void main(String[] args) {
    final Scanner scanner = new Scanner(System.in);
    scanner.nextLine();
    final int[] arr = Arrays.stream(scanner.nextLine().trim().split(" ")).mapToInt(Integer::parseInt).toArray();
    scanner.close();

    Node root = formTree(arr, 0, arr.length);

    System.out.println(checkBST(root) ? "Yes" : "No");
  }
}

using System;

class Solution
{
  private class Node
  {
    internal int data;
    internal Node left;
    internal Node right;

    internal Node(int _data, Node _left, Node _right)
    {
      data = _data;
      left = _left;
      right = _right;
    }
  }

  private static bool checkBST(Node root, int min, int max)
  {
    if (root == null)
    {
      return true;
    }

    int v = root.data;

    return (v > min && v < max && checkBST(root.left, min, v) && checkBST(root.right, v, max));
  }

  private static bool checkBST(Node root)
  {
    return checkBST(root, -1, 10001);
  }

  private static Node formTree(int[] data, int startIndex, int endIndex)
  {
    if (startIndex == endIndex)
    {
      return null;
    }

    int middleIndex = startIndex + (endIndex - startIndex) / 2;

    return new Node(
      data[middleIndex],
      formTree(data, startIndex, middleIndex),
      formTree(data, middleIndex + 1, endIndex)
      );
  }

  static void Main(string[] args)
  {
    Console.ReadLine();

    int[] arr = Array.ConvertAll(Console.ReadLine().Split(' '), arrTemp => Convert.ToInt32(arrTemp));

    Node root = formTree(arr, 0, arr.Length);

    Console.WriteLine(checkBST(root) ? "Yes" : "No");
  }
}

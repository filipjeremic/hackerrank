/*

Recursive solution (naturally, since it’s a tree problem)

The logic – basically, just bounds checking

Time complexity: O(n)
Space complexity: O(n) - for a balanced BST we would have log(n) here

*/

boolean checkBST(final Node root, final int min, final int max)
{
    if (root == null) return true;
    return root.data > min && root.data < max && checkBST(root.left, min, root.data) && checkBST(root.right, root.data, max);
}

boolean checkBST(final Node root)
{
    return checkBST(root, Integer.MIN_VALUE, Integer.MAX_VALUE);
}

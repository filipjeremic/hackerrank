/*

Recursive solution (naturally, since it’s a tree problem)

The logic – basically, just bounds checking

Time complexity: O(n)
Space complexity: O(n) - for a balanced BST we would have log(n) here

*/

bool checkBST(const Node *const root, const int min, const int max)
{
    if (root == nullptr) return true;
    return root->data > min && root->data < max && checkBST(root->left, min, root->data) && checkBST(root->right, root->data, max);
}

bool checkBST(const Node *const root)
{
    return checkBST(root, -1, 10001);
}

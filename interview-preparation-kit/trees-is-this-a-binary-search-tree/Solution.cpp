bool checkBST(const Node *const node, const int minValue, const int maxValue)
{
    if (node == nullptr)
    {
        return true;
    }

    return (
        node->data > minValue &&
        node->data < maxValue &&
        checkBST(node->left, minValue, node->data) &&
        checkBST(node->right, node->data, maxValue)
    );
}

bool checkBST(const Node *const root)
{
    return checkBST(root, -1, 10001);
}

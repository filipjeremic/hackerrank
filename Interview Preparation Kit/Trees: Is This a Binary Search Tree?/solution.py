# Recursive solution (naturally, since it’s a tree problem)

# The logic – basically, just bounds checking

# Time complexity: O(n)
# Space complexity: O(n) - for a balanced BST we would have log(n) here


def checkBST_recursive(root, min_value, max_value):
    if root is None:
        return True
    return root.data > min_value and root.data < max_value and checkBST_recursive(root.left, min_value, root.data) and checkBST_recursive(root.right, root.data, max_value)


def checkBST(root):
    return checkBST_recursive(root, -1, 10001)

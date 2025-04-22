def checkBST_node(node, min_value, max_value):
    if node is None:
        return True
    return (
        node.data > min_value
        and node.data < max_value
        and checkBST_node(node.left, min_value, node.data)
        and checkBST_node(node.right, node.data, max_value)
    )


def checkBST(root):
    return checkBST_node(root, 0, 10000)

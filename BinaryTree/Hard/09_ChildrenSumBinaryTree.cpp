/**
 * Check whether every non-leaf node satisfies:
 * node->data = left_child_data + right_child_data
 *
 * Approach:
 * 1. Leaf nodes always satisfy the property.
 * 2. Compute the sum of existing children.
 * 3. Check the current node.
 * 4. Recursively verify left and right subtrees.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H)  // recursion stack
 */

class Solution {
public:
    bool solve(Node* root) {
        if (!root)
            return true;

        if (!root->left && !root->right)
            return true;

        int childSum = 0;

        if (root->left)
            childSum += root->left->data;

        if (root->right)
            childSum += root->right->data;

        return (root->data == childSum) &&
               solve(root->left) &&
               solve(root->right);
    }

    bool isSumProperty(Node* root) {
        return solve(root);
    }
};
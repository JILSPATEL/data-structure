/**
 * Problem: Diameter of Binary Tree
 *
 * The diameter of a binary tree is the length of the longest path
 * between any two nodes in the tree. This path may or may not pass
 * through the root.
 *
 * Approach 1 (Optimized DFS) [Implemented]:
 * - Compute the height of each subtree.
 * - At every node, calculate:
 *       leftHeight + rightHeight
 * - Update the global diameter.
 * - Return height to the parent.
 *
 * Approach 2 (Brute Force):
 * - Compute heights for every node separately.
 * - Time Complexity: O(n²)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(h)
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right)
 *         : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    int diameter = 0;

    int dfs(TreeNode* root) {
        if (root == nullptr)
            return 0;

        int leftHeight = dfs(root->left);
        int rightHeight = dfs(root->right);

        diameter = max(diameter, leftHeight + rightHeight);

        return 1 + max(leftHeight, rightHeight);
    }

    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return diameter;
    }
};
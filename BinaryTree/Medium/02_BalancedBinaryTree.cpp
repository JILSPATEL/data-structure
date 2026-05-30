/**
 * Problem: Balanced Binary Tree
 *
 * Given a binary tree, determine whether it is height-balanced.
 *
 * A height-balanced binary tree is one in which the left and right
 * subtrees of every node differ in height by at most 1.
 *
 * Approach 1 (Optimized DFS) [Implemented]:
 * - Recursively compute the height of left and right subtrees.
 * - If any subtree is unbalanced, return -1.
 * - Otherwise return the height of the current subtree.
 *
 * Approach 2 (Brute Force):
 * - Compute heights separately for every node and check balance.
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
    int solve(TreeNode* root) {
        if (root == nullptr)
            return 0;

        int left = solve(root->left);
        if (left == -1)
            return -1;

        int right = solve(root->right);
        if (right == -1)
            return -1;

        if (abs(left - right) > 1)
            return -1;

        return 1 + max(left, right);
    }

    bool isBalanced(TreeNode* root) {
        return solve(root) != -1;
    }
};
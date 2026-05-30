/**
 * Problem: Binary Tree Maximum Path Sum
 *
 * A path is any sequence of nodes connected by edges.
 * The path does not need to pass through the root.
 *
 * Approach 1 (Optimized DFS) [Implemented]:
 * - For each node, compute the maximum gain from its left and right subtrees.
 * - Ignore negative gains by taking max(0, gain).
 * - Update the global answer using:
 *       root + leftGain + rightGain
 * - Return the best single branch to the parent.
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
    int maxSum = INT_MIN;

    int dfs(TreeNode* root) {
        if (root == nullptr)
            return 0;

        int leftGain = max(0, dfs(root->left));
        int rightGain = max(0, dfs(root->right));

        int currentPath =
            root->val + leftGain + rightGain;

        maxSum = max(maxSum, currentPath);

        return root->val + max(leftGain, rightGain);
    }

    int maxPathSum(TreeNode* root) {
        dfs(root);
        return maxSum;
    }
};
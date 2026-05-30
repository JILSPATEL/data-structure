/**
 * Problem: Maximum Depth of Binary Tree
 *
 * Given the root of a binary tree, return its maximum depth.
 *
 * Maximum depth is the number of nodes along the longest path
 * from the root node down to the farthest leaf node.
 *
 * Approach 1 (Recursive DFS) [Implemented]:
 * - For each node, recursively find the depth of its left and right subtrees.
 * - The depth of the current node is:
 *      1 + max(leftDepth, rightDepth)
 * - Base case: nullptr has depth 0.
 *
 * Approach 2 (Iterative BFS):
 * - Perform level-order traversal using a queue.
 * - Count the number of levels processed.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(h) for recursion stack,
 * where h is the height of the tree.
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

        int leftDepth = solve(root->left);
        int rightDepth = solve(root->right);

        return 1 + max(leftDepth, rightDepth);
    }

    int maxDepth(TreeNode* root) {
        return solve(root);
    }
};
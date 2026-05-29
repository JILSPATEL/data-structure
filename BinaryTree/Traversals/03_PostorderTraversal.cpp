/**
 * Problem: Binary Tree Postorder Traversal
 *
 * Given the root of a binary tree, return the postorder traversal
 * of its nodes' values.
 *
 * Postorder Traversal Order:
 *      Left -> Right -> Root
 *
 * ---------------------------------------------------------
 * Possible Approaches:
 *
 * 1. Recursive Traversal
 *    - Traverse left subtree.
 *    - Traverse right subtree.
 *    - Visit current node.
 *    - Time Complexity: O(N)
 *    - Space Complexity: O(H)
 *
 * 2. Iterative Traversal using Stack
 *    - Use one or two stacks to simulate recursion.
 *    - Time Complexity: O(N)
 *    - Space Complexity: O(H)
 *
 * ---------------------------------------------------------
 * Intuition:
 *
 * In postorder traversal, a node is processed only after
 * both its left and right subtrees have been processed.
 *
 * Order:
 *      Left -> Right -> Root
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

    void postorder(TreeNode* root, vector<int>& ans) {

        if (!root) {
            return;
        }

        // Left Subtree
        postorder(root->left, ans);

        // Right Subtree
        postorder(root->right, ans);

        // Root Node
        ans.push_back(root->val);
    }

    vector<int> postorderTraversal(TreeNode* root) {

        vector<int> ans;

        postorder(root, ans);

        return ans;
    }
};
/**
 * Problem: Binary Tree Preorder Traversal
 *
 * Given the root of a binary tree, return its preorder traversal.
 *
 * Preorder Traversal Order:
 *      Root -> Left -> Right
 *
 * ---------------------------------------------------------
 * Possible Approaches:
 *
 * 1. Recursive Traversal
 *    - Visit root.
 *    - Recursively traverse left subtree.
 *    - Recursively traverse right subtree.
 *    - Time Complexity: O(N)
 *    - Space Complexity: O(H)
 *
 * 2. Iterative Traversal using Stack
 *    - Use stack to simulate recursion.
 *    - Time Complexity: O(N)
 *    - Space Complexity: O(H)
 *
 * ---------------------------------------------------------
 * Intuition:
 *
 * For preorder traversal, process the current node first,
 * then recursively process the left subtree and right subtree.
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
    vector<int> preorderTraversal(TreeNode* root) {

        if (!root) {
            return {};
        }

        vector<int> ans;

        // Visit root
        ans.push_back(root->val);

        // Traverse left subtree
        vector<int> left = preorderTraversal(root->left);
        ans.insert(ans.end(), left.begin(), left.end());

        // Traverse right subtree
        vector<int> right = preorderTraversal(root->right);
        ans.insert(ans.end(), right.begin(), right.end());

        return ans;
    }
};
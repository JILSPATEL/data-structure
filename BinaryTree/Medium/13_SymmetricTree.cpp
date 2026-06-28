/**
 * Symmetric Tree
 *
 * Approach:
 * - A tree is symmetric if its left and right subtrees are mirror images.
 * - Compare:
 *      1. Values of both nodes must be equal.
 *      2. Left child of first node must match right child of second node.
 *      3. Right child of first node must match left child of second node.
 *
 * Time Complexity : O(N)
 * Space Complexity: O(H)
 *      H = height of tree (recursion stack)
 *
 * Alternative Approaches:
 * 1. Recursive DFS (Used Below)
 * 2. Iterative BFS using Queue
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
    bool check(TreeNode* node1, TreeNode* node2) {
        if (node1 == nullptr && node2 == nullptr) {
            return true;
        }

        if (node1 == nullptr || node2 == nullptr) {
            return false;
        }

        return (node1->val == node2->val &&
                check(node1->left, node2->right) &&
                check(node1->right, node2->left));
    }

    bool isSymmetric(TreeNode* root) {
        if (!root) {
            return true;
        }

        return check(root->left, root->right);
    }
};
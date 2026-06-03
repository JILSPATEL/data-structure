/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/**
 * Approach:
 * 1. If the current node is NULL, return NULL.
 * 2. If the current node is either p or q, return it.
 * 3. Search for p and q in the left and right subtrees.
 * 4. If both sides return non-NULL, the current node is the LCA.
 * 5. Otherwise, return the non-NULL result.
 *
 * Time Complexity : O(n)
 * Space Complexity: O(h)
 *      h = height of the tree
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(
        TreeNode* root,
        TreeNode* p,
        TreeNode* q
    ) {
        if (!root) {
            return nullptr;
        }

        if (root == p || root == q) {
            return root;
        }

        TreeNode* leftNode = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightNode = lowestCommonAncestor(root->right, p, q);

        if (leftNode && rightNode) {
            return root;
        }

        if (leftNode) {
            return leftNode;
        }

        return rightNode;
    }
};
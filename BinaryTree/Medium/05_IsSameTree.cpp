/**
 * Problem: Same Tree
 *
 * Given the roots of two binary trees p and q,
 * return true if they are structurally identical
 * and have the same node values.
 *
 * Approach 1 (Recursive DFS) [Implemented]:
 * - If both nodes are nullptr, return true.
 * - If one node is nullptr and the other is not, return false.
 * - Check:
 *      1. Current node values are equal.
 *      2. Left subtrees are identical.
 *      3. Right subtrees are identical.
 *
 * Approach 2 (Iterative BFS/Queue):
 * - Traverse both trees simultaneously using a queue.
 * - Compare corresponding nodes level by level.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(h)
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr)
            return true;

        if (p == nullptr || q == nullptr)
            return false;

        return (p->val == q->val) &&
               isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }
};
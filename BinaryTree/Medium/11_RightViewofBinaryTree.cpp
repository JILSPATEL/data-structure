/**
 * Right View of Binary Tree
 *
 * Approach:
 * - Traverse Right -> Left.
 * - First node visited at each level is part of the right view.
 *
 * Time Complexity : O(N)
 * Space Complexity: O(H)
 */

class Solution {
public:
    vector<int> res;

    void dfs(TreeNode* root, int level) {
        if (!root) return;

        if (level == res.size()) {
            res.push_back(root->val);
        }

        dfs(root->right, level + 1);
        dfs(root->left, level + 1);
    }

    vector<int> rightSideView(TreeNode* root) {
        dfs(root, 0);
        return res;
    }
};
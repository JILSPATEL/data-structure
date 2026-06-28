/**
 * Left View of Binary Tree
 *
 * Approach:
 * - Traverse Left -> Right.
 * - First node visited at each level is part of the left view.
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

        dfs(root->left, level + 1);
        dfs(root->right, level + 1);
    }

    vector<int> leftSideView(TreeNode* root) {
        dfs(root, 0);
        return res;
    }
};
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// House Robber III
// Given a binary tree with nonnegative node values, return the maximum amount
// that can be robbed without taking any pair of direct parent-child nodes.
// Example:
//   Input: [3,2,3,null,3,null,1]
//   Output: 7
//   Explanation: Rob the root 3, the left-right 3, and the rightmost leaf 1.
class Solution {
public:
    unordered_map<TreeNode*, int> dp;
    int rob(TreeNode* root) {
        if(!root){
            return 0;
        }
        if(dp.count(root)){
            return dp[root];
        }

        int take=root->val;

        if(root->left){
            take+=rob(root->left->left);
            take+=rob(root->left->right);
        }

        if(root->right){
            take+=rob(root->right->left);
            take+=rob(root->right->right);
        }

        int skip=rob(root->left)+rob(root->right);
        dp[root]=max(take,skip);
        return dp[root];

    }
};
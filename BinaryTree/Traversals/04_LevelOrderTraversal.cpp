/**
 * Problem: Binary Tree Level Order Traversal
 *
 * Given the root of a binary tree, return the level order
 * traversal of its nodes' values.
 *
 * Level Order Traversal:
 *      Visit nodes level by level from left to right.
 *
 * ---------------------------------------------------------
 * Possible Approaches:
 *
 * 1. BFS using Queue (Optimal)
 *    - Store nodes of the current level in a queue.
 *    - Process all nodes of a level before moving to the next.
 *    - Time Complexity: O(N)
 *    - Space Complexity: O(N)
 *
 * 2. DFS using Recursion
 *    - Pass current level as a parameter.
 *    - Store nodes according to their depth.
 *    - Time Complexity: O(N)
 *    - Space Complexity: O(H)
 *
 * ---------------------------------------------------------
 * Intuition:
 *
 * A queue naturally follows FIFO order, making it suitable
 * for processing nodes level by level.
 *
 * At each iteration:
 * 1. Store the current queue size.
 * 2. Process exactly those many nodes.
 * 3. Push their children into the queue.
 * 4. Store the current level's values.
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
    vector<vector<int>> levelOrder(TreeNode* root) {

        vector<vector<int>> ans;

        if (root == nullptr) {
            return ans;
        }

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {

            int levelSize = q.size();

            vector<int> currentLevel;

            for (int i = 0; i < levelSize; i++) {

                TreeNode* node = q.front();
                q.pop();

                currentLevel.push_back(node->val);

                if (node->left) {
                    q.push(node->left);
                }

                if (node->right) {
                    q.push(node->right);
                }
            }

            ans.push_back(currentLevel);
        }

        return ans;
    }
};
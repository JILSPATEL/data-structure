/**
 * Problem: Binary Tree Zigzag Level Order Traversal
 *
 * Given the root of a binary tree, return the zigzag level order traversal
 * of its nodes' values.
 *
 * Zigzag Traversal:
 * Level 0 -> Left to Right
 * Level 1 -> Right to Left
 * Level 2 -> Left to Right
 * and so on...
 *
 * Approaches:
 * 1. BFS + Reverse Alternate Levels
 *    - Store level normally.
 *    - Reverse every alternate level.
 *    - Time: O(N), Space: O(N)
 *
 * 2. BFS + Direct Placement (Used Below)
 *    - Create level array of size = number of nodes in current level.
 *    - Place node values at correct index based on traversal direction.
 *    - Avoids reversing.
 *    - Time: O(N), Space: O(N)
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

        // Stores final zigzag traversal
        vector<vector<int>> res;

        // Edge case: empty tree
        if (root == NULL)
            return res;

        queue<TreeNode*> q;
        q.push(root);

        // true  -> Left to Right
        // false -> Right to Left
        bool lTor = true;

        while (!q.empty()) {

            int size = q.size();

            // Current level result
            vector<int> level(size);

            for (int i = 0; i < size; i++) {

                TreeNode* node = q.front();
                q.pop();

                /*
                 * Determine correct index:
                 *
                 * Left to Right:
                 * i = 0,1,2,...
                 *
                 * Right to Left:
                 * size-1, size-2,...
                 */
                int idx = lTor ? i : size - i - 1;

                level[idx] = node->val;

                // Push children for next level
                if (node->left)
                    q.push(node->left);

                if (node->right)
                    q.push(node->right);
            }

            res.push_back(level);

            // Change traversal direction
            lTor = !lTor;
        }

        return res;
    }
};
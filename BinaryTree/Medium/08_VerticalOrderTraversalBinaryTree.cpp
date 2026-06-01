/**
 * LeetCode 987 - Vertical Order Traversal of a Binary Tree
 *
 * Approach:
 * 1. Perform DFS traversal and assign each node:
 *      - row = depth of node
 *      - col = horizontal distance from root
 *
 * 2. Store every node in a min-heap as:
 *      {column, row, value}
 *
 * 3. The priority queue automatically sorts nodes by:
 *      - column (ascending)
 *      - row (ascending)
 *      - value (ascending)
 *
 * 4. Pop nodes from the heap and group nodes having the same column.
 *
 * Time Complexity:
 *      O(N log N)
 *      N insertions + N deletions from priority queue.
 *
 * Space Complexity:
 *      O(N)
 *      Priority queue + recursion stack.
 *
 * Alternative Approaches:
 * 1. DFS + map<int, map<int, multiset<int>>>
 * 2. BFS + sorting vector of {col,row,val}
 * 3. DFS + vector + custom sort
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
    priority_queue<
        vector<int>,
        vector<vector<int>>,
        greater<vector<int>>
    > pq;

    void dfs(TreeNode* node, int row, int col) {
        if (!node)
            return;

        // Store {column, row, value}
        pq.push({col, row, node->val});

        dfs(node->left, row + 1, col - 1);
        dfs(node->right, row + 1, col + 1);
    }

    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<vector<int>> res;

        if (!root)
            return res;

        // Root coordinates
        int row = 0;
        int col = 0;

        pq.push({col, row, root->val});

        if (root->left)
            dfs(root->left, row + 1, col - 1);

        if (root->right)
            dfs(root->right, row + 1, col + 1);

        int prevCol = pq.top()[0];

        vector<int> currentColumn;

        while (!pq.empty()) {
            auto curr = pq.top();
            pq.pop();

            int col = curr[0];
            int row = curr[1];
            int val = curr[2];

            // New column encountered
            if (prevCol != col) {
                res.push_back(currentColumn);

                currentColumn.clear();
                prevCol = col;
            }

            currentColumn.push_back(val);
        }

        // Add the last column
        if (!currentColumn.empty())
            res.push_back(currentColumn);

        return res;
    }
};
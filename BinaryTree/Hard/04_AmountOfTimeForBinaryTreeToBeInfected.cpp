/**
 * LeetCode 2385 - Amount of Time for Binary Tree to Be Infected
 *
 * Approach:
 * 1. Convert the binary tree into an undirected graph using DFS.
 *    - Connect parent <-> child in both directions.
 * 2. Perform BFS starting from the infected node (start).
 * 3. Track the infection time for each node level by level.
 * 4. The maximum level reached during BFS is the answer.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 *
 * Approaches:
 * 1. Graph + BFS (Implemented)
 *    - Build an undirected graph and perform BFS from start node.
 *
 * 2. Single DFS Solution
 *    - Compute distances and subtree heights without explicitly
 *      constructing a graph.
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
    void buildGraph(TreeNode* node,
                    unordered_map<int, vector<int>>& adj) {
        if (!node) {
            return;
        }

        if (node->left) {
            adj[node->val].push_back(node->left->val);
            adj[node->left->val].push_back(node->val);

            buildGraph(node->left, adj);
        }

        if (node->right) {
            adj[node->val].push_back(node->right->val);
            adj[node->right->val].push_back(node->val);

            buildGraph(node->right, adj);
        }
    }

    int amountOfTime(TreeNode* root, int start) {
        unordered_map<int, vector<int>> adj;
        buildGraph(root, adj);

        unordered_set<int> vis;
        vis.insert(start);

        queue<pair<int, int>> q;
        q.push({start, 0});

        int time = 0;

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            int node = curr.first;
            int currTime = curr.second;

            time = max(time, currTime);

            for (auto& neb : adj[node]) {
                if (!vis.count(neb)) {
                    vis.insert(neb);
                    q.push({neb, currTime + 1});
                }
            }
        }

        return time;
    }
};
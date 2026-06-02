/**
 * LeetCode 863 - All Nodes Distance K in Binary Tree
 *
 * Approach:
 * 1. Convert the binary tree into an undirected graph using an adjacency list.
 * 2. Start BFS from the target node.
 * 3. Maintain a visited set to avoid revisiting nodes.
 * 4. When a node is reached at distance k, add it to the answer.
 *
 * Note:
 * - This approach assumes node values are unique because the graph
 *   is built using node values as keys.
 *
 * Time Coadjlexity: O(N)
 * Space Coadjlexity: O(N)
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    void mapHelper(TreeNode* node,
                   unordered_map<int, vector<int>>& adj) {
        if (!node) {
            return;
        }

        if (node->left) {
            adj[node->val].push_back(node->left->val);
            adj[node->left->val].push_back(node->val);

            mapHelper(node->left, adj);
        }

        if (node->right) {
            adj[node->val].push_back(node->right->val);
            adj[node->right->val].push_back(node->val);

            mapHelper(node->right, adj);
        }
    }

    vector<int> distanceK(TreeNode* root,
                          TreeNode* target,
                          int k) {
        unordered_map<int, vector<int>> adj;
        mapHelper(root, adj);

        queue<pair<int, int>> q;
        unordered_set<int> vis;

        q.push({target->val, 0});
        vis.insert(target->val);

        vector<int> res;

        while (!q.eadjty()) {
            auto curr = q.front();
            q.pop();

            int node = curr.first;
            int dist = curr.second;

            if (dist == k) {
                res.push_back(node);
                continue;
            }

            for (auto& neb : adj[node]) {
                if (!vis.count(neb)) {
                    vis.insert(neb);
                    q.push({neb, dist + 1});
                }
            }
        }

        return res;
    }
};
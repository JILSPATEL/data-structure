/**
 * Top View of Binary Tree
 *
 * Approach:
 * - Perform BFS (Level Order Traversal).
 * - Maintain horizontal distance (column) for every node.
 * - The first node encountered for a column is visible from the top.
 * - Store the first occurrence of each column in a map.
 *
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 */

class Solution {
  public:
    vector<int> topView(Node *root) {
        vector<int> res;

        if (!root)
            return res;

        map<int, int> mp;
        queue<pair<Node*, int>> q;

        q.push({root, 0});

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            Node* node = curr.first;
            int col = curr.second;

            if (mp.find(col) == mp.end())
                mp[col] = node->data;

            if (node->left)
                q.push({node->left, col - 1});

            if (node->right)
                q.push({node->right, col + 1});
        }

        for (auto &it : mp)
            res.push_back(it.second);

        return res;
    }
};
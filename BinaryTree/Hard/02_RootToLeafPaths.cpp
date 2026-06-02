/**
 * Root to Leaf Paths
 *
 * Approach 1: DFS (Recursive)
 * - Maintain a path vector from root to current node.
 * - Add the current node to the path.
 * - If a leaf node is reached, store the path in the result.
 * - Recursively explore the left and right subtrees.
 *
 * Time Complexity: O(N * H)
 *   N = Number of nodes
 *   H = Height of tree (due to path copying)
 *
 * Space Complexity: O(H)
 *   Recursive stack space.
 */

/*
Definition for Node
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};
*/

class Solution {
public:
    vector<vector<int>> res;

    void dfs(Node* node, vector<int> path) {
        if (!node) {
            return;
        }

        path.push_back(node->data);

        if (!node->left && !node->right) {
            res.push_back(path);
            return;
        }

        if (node->left) {
            dfs(node->left, path);
        }

        if (node->right) {
            dfs(node->right, path);
        }
    }

    vector<vector<int>> Paths(Node* root) {
        if (!root) {
            return res;
        }

        vector<int> path;
        dfs(root, path);

        return res;
    }
};
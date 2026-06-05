/**
 * Burning Tree Problem
 *
 * Given a binary tree and a target node, determine the minimum time
 * required to burn the entire tree if the fire starts from the target node.
 *
 * Approach 1 (Implemented):
 * -------------------------
 * 1. Convert the binary tree into an undirected graph.
 *    - Connect parent ↔ child edges.
 * 2. Perform BFS starting from the target node.
 * 3. Each BFS level represents one unit of time.
 * 4. The maximum distance from the target node to any other node
 *    is the answer.
 *
 * Time Complexity:
 * ----------------
 * Building Graph : O(N)
 * BFS Traversal  : O(N)
 * Total          : O(N)
 *
 * Space Complexity:
 * -----------------
 * Adjacency List : O(N)
 * Visited Set    : O(N)
 * BFS Queue      : O(N)
 * Total          : O(N)
 *
 * Approach 2 (Alternative):
 * -------------------------
 * Store parent pointers for every node and perform BFS using:
 * - left child
 * - right child
 * - parent
 *
 * This avoids explicitly creating an adjacency list.
 */

/*
class Node {
  public:
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/

class Solution {
  public:

    /**
     * Creates an undirected graph representation of the tree.
     *
     * Example:
     *
     *        1
     *       / \
     *      2   3
     *
     * Graph:
     * 1 ↔ 2
     * 1 ↔ 3
     */
    void buildGraph(Node* root,
                    unordered_map<int, vector<int>>& adjacencyList) {

        if (!root) {
            return;
        }

        if (root->left) {
            adjacencyList[root->data].push_back(root->left->data);
            adjacencyList[root->left->data].push_back(root->data);

            buildGraph(root->left, adjacencyList);
        }

        if (root->right) {
            adjacencyList[root->data].push_back(root->right->data);
            adjacencyList[root->right->data].push_back(root->data);

            buildGraph(root->right, adjacencyList);
        }
    }

    int minTime(Node* root, int target) {

        // Step 1: Convert tree into an undirected graph.
        unordered_map<int, vector<int>> adjacencyList;
        buildGraph(root, adjacencyList);

        // Step 2: BFS from target node.
        queue<pair<int, int>> bfsQueue;
        unordered_set<int> visited;

        bfsQueue.push({target, 0});
        visited.insert(target);

        int minimumTime = 0;

        while (!bfsQueue.empty()) {

            auto [currentNode, currentTime] = bfsQueue.front();
            bfsQueue.pop();

            // Track the maximum time reached.
            minimumTime = max(minimumTime, currentTime);

            // Visit all adjacent nodes.
            for (int neighbor : adjacencyList[currentNode]) {

                if (!visited.count(neighbor)) {

                    visited.insert(neighbor);

                    bfsQueue.push({
                        neighbor,
                        currentTime + 1
                    });
                }
            }
        }

        return minimumTime;
    }
};
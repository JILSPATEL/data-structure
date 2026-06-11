/**
 * Problem: Course Schedule II / Topological Sort
 *
 * Given:
 * ------
 * V      -> Total vertices/nodes
 * edges  -> Directed edges
 *
 * We need to return a valid ordering of nodes
 * such that:
 *
 * If there is an edge:
 *      u -> v
 *
 * then u must appear before v.
 *
 * Example 1:
 * Input: V = 4, edges = [[1,0],[2,0],[3,1],[3,2]]
 * Output: [0,1,2,3]
 * Explanation: Valid topological ordering
 *
 * Example 2:
 * Input: V = 2, edges = [[1,0],[0,1]]
 * Output: []
 * Explanation: Cycle exists, no valid ordering
 *
 * Example 3:
 * Input: V = 3, edges = [[0,1],[0,2]]
 * Output: [1,2,0] or [2,1,0]
 * Explanation: Multiple valid orderings exist
 *
 * ---------------------------------------------------
 * Algorithm Used:
 * Kahn's Algorithm (BFS Topological Sort)
 * ---------------------------------------------------
 *
 * Core Idea:
 * ----------
 * 1. Find indegree of every node.
 *    indegree = number of incoming edges.
 *
 * 2. Push all nodes with indegree 0 into queue.
 *    (These nodes have no dependency)
 *
 * 3. Perform BFS:
 *      - Remove node from queue
 *      - Add it into answer
 *      - Reduce indegree of neighbors
 *      - If neighbor indegree becomes 0,
 *        push it into queue
 *
 * 4. Final BFS order gives topological ordering.
 *
 * ---------------------------------------------------
 * Time Complexity:
 * O(V + E)
 *
 * Space Complexity:
 * O(V + E)
 */

class Solution {
public:

    vector<int> findOrder(int V,
                          vector<vector<int>>& edges) {

        /**
         * Adjacency List
         */
        vector<vector<int>> adj(V);

        /**
         * Create graph
         *
         * Edge:
         * u -> v
         */
        for (auto &it : edges) {

            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
        }

        /**
         * Indegree array
         *
         * indegree[i] =
         * number of incoming edges
         */
        vector<int> inDeg(V, 0);

        /**
         * Calculate indegree
         */
        for (int i = 0; i < V; i++) {

            for (auto &it : adj[i]) {

                inDeg[it]++;
            }
        }

        /**
         * BFS Queue
         */
        queue<int> q;

        /**
         * Push nodes with indegree 0
         */
        for (int i = 0; i < V; i++) {

            if (inDeg[i] == 0) {

                q.push(i);
            }
        }

        /**
         * Stores topological ordering
         */
        vector<int> visited;

        /**
         * Standard BFS
         */
        while (!q.empty()) {

            // Get front node
            int node = q.front();
            q.pop();

            // Add into answer
            visited.push_back(node);

            /**
             * Traverse neighbors
             */
            for (auto &it : adj[node]) {

                // Remove dependency
                inDeg[it]--;

                /**
                 * If indegree becomes 0
                 * push into queue
                 */
                if (inDeg[it] == 0) {

                    q.push(it);
                }
            }
        }

        /**
         * If cycle exists,
         * topological ordering is impossible
         */
        if (visited.size() != V) {

            return {};
        }

        return visited;
    }
};
/**
 * Problem: Detect Cycle in Directed Graph using BFS (Kahn's Algorithm)
 *
 * Approach:
 * 1. Create adjacency list from given edges.
 * 2. Calculate indegree of every node.
 * 3. Push all nodes with indegree 0 into queue.
 * 4. Perform BFS:
 *      - Remove node from queue
 *      - Reduce indegree of its neighbors
 *      - If neighbor indegree becomes 0, push into queue
 * 5. Count visited nodes.
 * 6. If visited nodes != total vertices,
 *    then graph contains a cycle.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
 */

class Solution {
public:
    bool isCyclic(int V, vector<vector<int>>& edges) {

        // Step 1: Create adjacency list
        vector<vector<int>> adj(V);

        for (auto &it : edges) {
            adj[it[0]].push_back(it[1]);
        }

        // Step 2: Calculate indegree
        vector<int> inDeg(V, 0);

        for (int i = 0; i < V; i++) {
            for (auto &it : adj[i]) {
                inDeg[it]++;
            }
        }

        // Step 3: Push nodes having indegree 0
        queue<int> q;

        for (int i = 0; i < V; i++) {
            if (inDeg[i] == 0) {
                q.push(i);
            }
        }

        // Step 4: BFS Traversal
        int visited = 0;

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            visited++;

            for (auto &it : adj[node]) {

                inDeg[it]--;

                if (inDeg[it] == 0) {
                    q.push(it);
                }
            }
        }

        // Step 5: If all nodes are not visited,
        // cycle exists
        return visited != V;
    }
};

/*
Example:

Input:
V = 4
edges = {{0,1}, {1,2}, {2,3}}

Graph:
0 → 1 → 2 → 3

Indegree:
0 : 0
1 : 1
2 : 1
3 : 1

Queue initially:
[0]

Processing order:
0 → 1 → 2 → 3

Visited Nodes = 4
Total Nodes   = 4

visited == V
=> No Cycle

Output:
false



Cycle Example:

Input:
V = 4
edges = {{0,1}, {1,2}, {2,3}, {3,1}}

Graph:
0 → 1 → 2 → 3
     ↑       ↓
     └───────┘

Indegree:
0 : 0
1 : 2
2 : 1
3 : 1

Queue initially:
[0]

After removing 0:
No new node gets indegree 0

Visited Nodes = 1
Total Nodes   = 4

visited != V
=> Cycle Exists

Output:
true
*/
/*
Problem 2: Count Valid Bias Nodes
Pattern: Directed Graph, Indegree, Outdegree, Neighbor Types

1. Understand the Problem:
   - We are given a directed graph representing neural network operations.
   - Each node represents an operation such as Conv, Bias, ReLU, or Other.
   - An edge u -> v means the output of operation u is used by operation v.
   - We need to count the Bias nodes satisfying all the given conditions.

2. Conditions for a Valid Bias Node:
   A Bias node is valid only if:
   - Its type is "Bias".
   - It has exactly one incoming edge (indegree = 1).
   - It has exactly one outgoing edge (outdegree = 1).
   - Its only incoming neighbor is a "Conv" node.
   - Its only outgoing neighbor is a "ReLU" node.

   Valid pattern:
       Conv -> Bias -> ReLU

3. What Makes a Bias Node Invalid?
   - Multiple incoming edges to Bias.
   - Multiple outgoing edges from Bias.
   - Its incoming neighbor is not Conv.
   - Its outgoing neighbor is not ReLU.
   - Even if Conv and ReLU are connected through Bias, any
     additional incoming or outgoing edge makes Bias invalid.

4. Approach:
   Step 1:
   - Store the type of every node.
   - Build the adjacency list for outgoing edges.
   - Maintain an adjacency list for incoming edges, or store the
     unique parent and child when their degrees are exactly one.

   Step 2:
   - For every edge u -> v:
       * Increment indegree[v].
       * Increment outdegree[u].
       * Store u as an incoming neighbor of v.
       * Store v as an outgoing neighbor of u.

   Step 3:
   - Iterate through every node u.
   - Check whether type[u] is "Bias".
   - Check whether indegree[u] == 1.
   - Check whether outdegree[u] == 1.
   - Check whether its only incoming neighbor is "Conv".
   - Check whether its only outgoing neighbor is "ReLU".
   - If all conditions hold, increment the answer.

5. Conceptual Code:

   if (type[u] == "Bias" &&
       indegree[u] == 1 &&
       outdegree[u] == 1 &&
       type[parent[u]] == "Conv" &&
       type[child[u]] == "ReLU") {
       answer++;
   }

   Note:
   - Access parent[u] and child[u] only after confirming that
     the incoming and outgoing degrees are both exactly one.

6. Complexity Analysis:
   - Time Complexity: O(N + M)
     We process all N nodes and M edges.
   - Space Complexity: O(N + M)
     We store node types, adjacency lists, and degree information.

7. Interview Recognition:
   - When asked to count graph nodes based on incoming and outgoing
     connections, think of indegree, outdegree, and neighbor types.
   - There is no need to enumerate all possible paths.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<string> type(N + 1);
    vector<vector<int>> adj(N + 1);

    vector<int> indegree(N + 1, 0);
    vector<int> outdegree(N + 1, 0);

    // Read node types
    for (int i = 1; i <= N; i++) {
        cin >> type[i];
    }

    // Read directed edges
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);

        outdegree[u]++;
        indegree[v]++;
    }

    int ans = 0;

    // Check every Bias node
    for (int u = 1; u <= N; u++) {
        if (type[u] != "Bias") {
            continue;
        }

        // Bias must have exactly one incoming and outgoing edge
        if (indegree[u] != 1 || outdegree[u] != 1) {
            continue;
        }

        int parent = -1;

        // Find the incoming neighbor
        for (int v = 1; v <= N; v++) {
            for (int next : adj[v]) {
                if (next == u) {
                    parent = v;
                    break;
                }
            }

            if (parent != -1) {
                break;
            }
        }

        // Find the outgoing neighbor
        int child = adj[u][0];

        // Check Conv -> Bias -> ReLU
        if (parent != -1 &&
            type[parent] == "Conv" &&
            type[child] == "ReLU") {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}

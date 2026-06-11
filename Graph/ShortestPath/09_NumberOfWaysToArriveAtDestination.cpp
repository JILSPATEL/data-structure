/**
 * Problem: Number of Ways to Arrive at Destination
 *
 * Description:
 * Count the number of shortest paths from node 0 to node n-1
 * in a weighted undirected graph.
 *
 * Example 1:
 * Input: n=6, roads=[[0,1,4],[0,2,1],[1,3,2],[2,1,3],[1,4,1],[4,3,1],[2,4,5],[4,5,2],[3,5,1]]
 * Output: 1
 * Explanation: Only one shortest path exists
 *
 * Example 2:
 * Input: n=4, roads=[[0,1,1],[1,2,1],[2,3,1],[0,3,3],[1,3,2]]
 * Output: 2
 * Explanation: Two different shortest paths to destination
 *
 * Example 3:
 * Input: n=3, roads=[[0,1,1],[0,2,1],[1,2,1]]
 * Output: 1
 * Explanation: Direct paths both have same distance
 *
 * Approach 1: Brute Force
 * - Generate all possible paths from source (0) to destination (n-1)
 * - Find shortest distance and count paths having that distance
 * - Time Complexity: Exponential
 * - Not feasible
 *
 * Approach 2: Dijkstra + Path Counting (Optimal)
 * - Use Dijkstra to compute shortest distance
 * - Maintain an additional "ways" array
 *
 * ways[i] = number of shortest ways to reach node i
 *
 * Cases:
 *
 * 1. Found smaller distance:
 *      dist[newNode] = newCost
 *      ways[newNode] = ways[node]
 *
 * 2. Found same shortest distance:
 *      ways[newNode] += ways[node]
 *
 * Why?
 * - Smaller distance means previous paths are useless
 * - Equal distance means we found one more shortest path
 *
 * Time Complexity:
 *      O((V+E)logV)
 *
 * Space Complexity:
 *      O(V+E)
 */

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {

        // Step 1: Create adjacency list
        vector<vector<pair<int,int>>> adj(n);

        for(auto &it:roads){
            int u=it[0];
            int v=it[1];
            int wt=it[2];

            adj[u].push_back({v,wt});
            adj[v].push_back({u,wt});
        }

        // Min Heap => {distance,node}
        priority_queue<
            pair<long long,int>,
            vector<pair<long long,int>>,
            greater<pair<long long,int>>
        > pq;

        // Store shortest distance
        vector<long long> dist(n,LLONG_MAX);

        // Store count of shortest paths
        vector<long long> ways(n,0);

        int mod=1e9+7;

        // Source initialization
        dist[0]=0;
        ways[0]=1;

        pq.push({0,0});

        while(!pq.empty()){

            auto curr=pq.top();
            pq.pop();

            long long currDist=curr.first;
            int node=curr.second;

            // Ignore outdated entries
            if(currDist>dist[node])
                continue;

            // Traverse neighbours
            for(auto &neb:adj[node]){

                int newNode=neb.first;
                long long wt=neb.second;

                long long newCost=currDist+wt;

                // Case 1:
                // Found shorter path
                if(newCost<dist[newNode]){

                    dist[newNode]=newCost;

                    // Copy ways from parent node
                    ways[newNode]=ways[node];

                    pq.push({newCost,newNode});
                }

                // Case 2:
                // Found another shortest path
                else if(newCost==dist[newNode]){

                    ways[newNode]=
                    (ways[newNode]+ways[node])%mod;
                }
            }
        }

        return ways[n-1]%mod;
    }
};
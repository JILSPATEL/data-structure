/**
 * Problem: Find the City With the Smallest Number of Neighbors at a Threshold Distance
 *
 * Description:
 * Given n cities and distance limits, find the city with
 * the smallest number of neighbors within threshold distance.
 *
 * Example 1:
 * Input: n=4, edges=[[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold=4
 * Output: 3
 * Explanation: City 3 can reach cities {0,1,2} which equals threshold
 *
 * Example 2:
 * Input: n=5, edges=[[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold=2
 * Output: 0
 * Explanation: City 0 has minimum neighbors within distance 2
 *
 * Example 3:
 * Input: n=6, edges=[[0,1,2],[0,2,4],[1,2,3],[1,3,1],[2,3,1],[2,4,5],[3,4,1],[3,5,3],[4,5,2]], distanceThreshold=3
 * Output: 5
 * Explanation: City 5 has fewest neighbors within threshold
 *
 * Approach: Dijkstra from every city
 *
 * Idea:
 * - Treat each city as a source node.
 * - Run Dijkstra's algorithm from that city to find the shortest
 *   distance to every other city.
 * - Count how many cities are reachable within the threshold distance.
 * - Keep track of the city with minimum reachable count.
 * - If multiple cities have the same count,
 *   return the city with the greater index.
 *
 * Why Dijkstra?
 * - Graph has weighted edges.
 * - We need shortest paths from one source to all nodes.
 * - Dijkstra efficiently finds shortest paths for non-negative weights.
 *
 * Steps:
 * 1. Create adjacency list.
 * 2. For every city:
 *      a) Run Dijkstra.
 *      b) Find shortest distance to all cities.
 *      c) Count cities with distance <= threshold.
 *      d) Update answer if current count is smaller.
 *
 * Time Complexity:
 * - Dijkstra for one node = O(E logV)
 * - Running for all nodes = O(V * E logV)
 *
 * Space Complexity:
 * - Adjacency list = O(E)
 * - Distance array = O(V)
 * - Priority queue = O(V)
 */

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int th) {

        // Adjacency list
        // adj[node] = {neighbor, weight}
        vector<vector<pair<int,int>>> adj(n);

        // Build graph
        for(auto &edge : edges){
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }

        // Stores final answer city
        int cityNo = -1;

        // Stores minimum reachable cities count
        int minCity = n;

        // Run Dijkstra from every city
        for(int src=0; src<n; src++){

            // Distance array
            vector<int> dist(n, INT_MAX);

            /*
                Min heap structure:

                {distance, node}

                Smallest distance remains on top
            */
            priority_queue<
                pair<int,int>,
                vector<pair<int,int>>,
                greater<pair<int,int>>
            > pq;

            // Start from source city
            pq.push({0, src});
            dist[src] = 0;

            //---------------- Dijkstra ----------------//
            while(!pq.empty()){

                auto curr = pq.top();
                pq.pop();

                int currWt = curr.first;
                int currNode = curr.second;

                /*
                    Skip stale entries

                    Example:
                    If node already got shorter path,
                    old larger distance in heap
                    becomes useless.
                */
                if(currWt > dist[currNode])
                    continue;

                // Explore neighbors
                for(auto &neb : adj[currNode]){

                    int nextNode = neb.first;

                    // Total distance to neighbor
                    int nextCost = currWt + neb.second;

                    /*
                        Relaxation step

                        If new path is shorter,
                        update distance and push
                        into priority queue.
                    */
                    if(nextCost < dist[nextNode]){

                        dist[nextNode] = nextCost;

                        pq.push({
                            nextCost,
                            nextNode
                        });
                    }
                }
            }

            //---------------- Count reachable cities ----------------//

            int cnt = 0;

            for(int i=0; i<n; i++){

                if(dist[i] <= th)
                    cnt++;
            }

            /*
                Update answer

                <= is important because
                if tie occurs, we need
                larger index city.
            */
            if(cnt <= minCity){

                minCity = cnt;
                cityNo = src;
            }
        }

        return cityNo;
    }
};
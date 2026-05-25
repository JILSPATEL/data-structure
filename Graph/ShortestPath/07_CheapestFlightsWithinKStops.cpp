/**
 * Problem: Cheapest Flights Within K Stops
 *
 * Description:
 * Given n cities and flight connections:
 *      flights[i] = {u, v, cost}
 *
 * Find the minimum cost from src → dst
 * with at most k stops.
 *
 * ----------------------------------------------------
 * Approach 1: Normal Queue (BFS Level Traversal)
 * ----------------------------------------------------
 *
 * Idea:
 * - Each BFS level represents one stop.
 * - Store:
 *      {stops, {node, cost}}
 *
 * - Explore all nodes level-wise.
 * - Update cost only if a cheaper path is found.
 *
 * Why queue works?
 * - We mainly care about limiting stops.
 * - BFS naturally processes paths in increasing
 *   number of stops.
 *
 * Time Complexity:
 *      O(E)
 *
 * Space Complexity:
 *      O(V + E)
 *
 *
 * ----------------------------------------------------
 * Approach 2: Priority Queue (Dijkstra Modified)
 * ----------------------------------------------------
 *
 * Normal Dijkstra:
 *
 *      dist[v] = dist[u] + wt
 *
 * and one distance per node is enough.
 *
 * Here one distance per node is NOT enough.
 *
 * Example:
 *
 *      A reached with:
 *
 *      cost = 100 stops = 1
 *      cost = 80  stops = 3
 *
 * Cheaper path may consume extra stops,
 * causing future paths to become invalid.
 *
 * Therefore store:
 *
 *      dist[node][stops]
 *
 * Priority queue stores:
 *
 *      {cost, {node, stops}}
 *
 * Time Complexity:
 *      O((V + E)log(V * K))
 *
 * Space Complexity:
 *      O(V * K)
 */


// Approach 1: Normal Queue (BFS Level Traversal)

class Solution {
public:
    int findCheapestPrice(
        int n,
        vector<vector<int>>& flights,
        int src,
        int dst,
        int k
    ) {
        vector<vector<pair<int, int>>> adj(n);

        for (auto& edge : flights) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        // Minimum cost to reach node
        vector<int> minCost(n, 1e9);

        // {stops, {node, cost}}
        queue<pair<int, pair<int, int>>> q;

        q.push({0, {src, 0}});
        minCost[src] = 0;

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            int stops = curr.first;
            int node = curr.second.first;
            int cost = curr.second.second;

            if (stops > k)
                continue;

            for (auto& neb : adj[node]) {
                int adjNode = neb.first;
                int wt = neb.second;
                int newCost = cost + wt;

                if (newCost < minCost[adjNode]) {
                    minCost[adjNode] = newCost;
                    q.push({stops + 1, {adjNode, newCost}});
                }
            }
        }

        return minCost[dst] == 1e9 ? -1 : minCost[dst];
    }
};


// Approach 2: Priority Queue (Dijkstra Modified)

class Solution {
public:
    int findCheapestPrice(
        int n,
        vector<vector<int>>& flights,
        int src,
        int dst,
        int k
    ) {
        vector<vector<pair<int, int>>> adj(n);

        for (auto& edge : flights) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        // dist[node][stops]
        vector<vector<int>> dist(
            n,
            vector<int>(k + 2, INT_MAX)
        );

        // {cost, {node, stops}}
        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<pair<int, pair<int, int>>>
        > pq;

        pq.push({0, {src, 0}});
        dist[src][0] = 0;

        while (!pq.empty()) {
            auto curr = pq.top();
            pq.pop();

            int currCost = curr.first;
            int currNode = curr.second.first;
            int currStops = curr.second.second;

            // Destination reached
            if (currNode == dst)
                return currCost;

            if (currStops > k)
                continue;

            // Ignore outdated state
            if (currCost > dist[currNode][currStops])
                continue;

            for (auto& neb : adj[currNode]) {
                int nextNode = neb.first;
                int wt = neb.second;
                int newCost = currCost + wt;

                if (newCost < dist[nextNode][currStops + 1]) {
                    dist[nextNode][currStops + 1] = newCost;
                    pq.push({newCost, {nextNode, currStops + 1}});
                }
            }
        }

        return -1;
    }
};

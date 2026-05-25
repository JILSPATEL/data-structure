/**
 * Problem: Minimum Effort Path
 *
 * Description:
 * Given a grid of heights, find a path from top-left (0,0)
 * to bottom-right (n-1,m-1) such that the effort is minimized.
 *
 * Effort of a path:
 * Maximum absolute difference between heights of consecutive cells.
 *
 * Approaches:
 *
 * 1) Brute Force:
 *    - Generate all possible paths
 *    - Calculate maximum difference for each path
 *    - Take minimum
 *    - Time: Exponential
 *
 * 2) Binary Search + BFS/DFS:
 *    - Binary search answer on effort
 *    - Check if destination reachable
 *    - Time: O(N*M*log(MaxHeight))
 *
 * 3) Dijkstra (Optimal) [Used]
 *    - Treat each cell as graph node
 *    - Weight between cells:
 *      abs(height1-height2)
 *
 *    Difference from normal Dijkstra:
 *    Normal:
 *      dist[v] = dist[u] + weight
 *
 *    Here:
 *      dist[v] = max(currentEffort, edgeWeight)
 *
 *    Reason:
 *    Path effort depends on maximum edge weight,
 *    not sum of weights.
 *
 * Time Complexity:
 * O((N*M) log(N*M))
 *
 * Space Complexity:
 * O(N*M)
 */

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {

        int n = heights.size();
        int m = heights[0].size();

        // Stores minimum effort needed to reach each cell
        vector<vector<int>> dist(
            n, vector<int>(m, INT_MAX)
        );

        // {effort,{row,col}}
        priority_queue<
            pair<int,pair<int,int>>,
            vector<pair<int,pair<int,int>>>,
            greater<pair<int,pair<int,int>>>
        > pq;

        dist[0][0] = 0;
        pq.push({0,{0,0}});

        vector<pair<int,int>> dir = {
            {0,1},
            {1,0},
            {-1,0},
            {0,-1}
        };

        while(!pq.empty()){

            auto curr = pq.top();
            pq.pop();

            int effort = curr.first;
            int row = curr.second.first;
            int col = curr.second.second;

            // Skip outdated entries
            if(effort > dist[row][col])
                continue;

            // Reached destination
            if(row==n-1 && col==m-1)
                return effort;

            for(auto &d : dir){

                int x = row + d.first;
                int y = col + d.second;

                if(x>=0 && y>=0 && x<n && y<m){

                    // Edge weight
                    int currDiff =
                        abs(
                            heights[x][y]
                            -
                            heights[row][col]
                        );

                    // Maximum effort till now
                    int newEffort =
                        max(effort,currDiff);

                    if(newEffort < dist[x][y]){

                        dist[x][y] = newEffort;

                        pq.push(
                            {newEffort,{x,y}}
                        );
                    }
                }
            }
        }

        return 0;
    }
};
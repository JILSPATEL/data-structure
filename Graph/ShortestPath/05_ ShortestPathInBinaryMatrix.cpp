/**
 * Problem: Shortest Path in Binary Matrix using Dijkstra
 *
 * Description:
 * Given an n x n binary matrix grid:
 *
 * - 0 -> empty cell (can move)
 * - 1 -> blocked cell
 *
 * Find the shortest path length from:
 *      (0,0) → (n−1,n−1)
 *
 * Movement allowed in 8 directions:
 *
 *      ↖ ↑ ↗
 *      ←   →
 *      ↙ ↓ ↘
 *
 * Return -1 if no valid path exists.
 *
 * ---------------------------------------------------------
 * Possible Approaches:
 *
 * 1) BFS (Optimal for this problem)
 *    - Since every movement cost = 1
 *    - BFS directly gives shortest path.
 *
 *    Time: O(n²)
 *    Space: O(n²)
 *
 * 2) Dijkstra
 *    - Use when edge weights may differ.
 *    - Maintain shortest distance for each cell.
 *    - Use min heap to always process minimum distance node.
 *
 *    Time: O(n² log(n²))
 *    Space: O(n²)
 *
 * Example 1:
 * Input: grid = [[0,1],[1,0]]
 * Output: 2
 * Explanation: Path: (0,0) → (1,1) with diagonal move
 *
 * Example 2:
 * Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
 * Output: 4
 * Explanation: Navigate around obstacles
 *
 * Example 3:
 * Input: grid = [[1,0],[0,1]]
 * Output: -1
 * Explanation: No valid path exists
 *
 * ---------------------------------------------------------
 * Dijkstra Idea:
 *
 * dist[i][j]
 * = shortest distance found till now to reach cell (i,j)
 *
 * Min Heap stores:
 *      {distance,{row,col}}
 *
 * Steps:
 *
 * 1. Initialize dist[][] with INF
 *
 * 2. Start:
 *      dist[0][0]=1
 *      push {1,{0,0}}
 *
 * 3. Pop minimum distance node
 *
 * 4. Explore all 8 neighbours
 *
 * 5. Relax edge:
 *
 *      if(currDist+1 < dist[x][y])
 *      {
 *          dist[x][y]=currDist+1;
 *          push into heap
 *      }
 *
 * 6. Continue until destination found
 *
 */

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {

        int n = grid.size();

        // Start or destination blocked
        if(grid[0][0]==1 || grid[n-1][n-1]==1)
            return -1;

        /*
            Distance matrix

            dist[i][j]
            = shortest distance from source
              to cell (i,j)
        */
        vector<vector<int>> dist(
            n,
            vector<int>(n,INT_MAX)
        );

        /*
            8 directions
        */
        vector<pair<int,int>> dir = {
            {-1,-1},{-1,0},{-1,1},
            {0,-1},         {0,1},
            {1,-1},{1,0},{1,1}
        };

        /*
            Min Heap

            pair:
            {
                distance,
                {
                    row,
                    col
                }
            }
        */
        priority_queue<
            pair<int,pair<int,int>>,
            vector<pair<int,pair<int,int>>>,
            greater<pair<int,pair<int,int>>>
        > pq;

        // Source initialization
        dist[0][0]=1;

        pq.push({1,{0,0}});

        while(!pq.empty()) {

            auto curr = pq.top();
            pq.pop();

            int currDist = curr.first;
            int row = curr.second.first;
            int col = curr.second.second;

            /*
                Ignore outdated entries

                Example:

                Heap:
                {7,(2,3)}
                {5,(2,3)}

                Since shorter distance already
                exists, ignore 7.
            */
            if(currDist > dist[row][col])
                continue;

            // Destination reached
            if(row==n-1 && col==n-1)
                return currDist;

            // Explore all neighbours
            for(auto &move:dir){

                int x = row + move.first;
                int y = col + move.second;

                // Valid cell check
                if(x>=0 && x<n &&
                   y>=0 && y<n &&
                   grid[x][y]==0){

                    /*
                        Relaxation step

                        old distance:
                        dist[x][y]

                        new distance:
                        currDist+1
                    */
                    if(currDist+1 < dist[x][y]){

                        dist[x][y]=currDist+1;

                        pq.push(
                            {
                                currDist+1,
                                {x,y}
                            }
                        );
                    }
                }
            }
        }

        return -1;
    }
};
//DFS
class Solution {
	public:
	int n;
	int m;
	int dfs(vector<vector<int>> & grid, int i, int j) {
		grid[i][j] = 0;
		int size = 1;
		vector<pair<int, int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0},
		{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
		
		for(auto &vec:dir){
		    int x=i+vec.first;
		    int y=j+vec.second;
		    if(x>=0 && y>=0 && x<n && y<m && grid[x][y]==1){
		        size+=dfs(grid,x,y);
		    }
		}
		return size;
	}
	int findMaxArea(vector<vector<int>> & grid) {
		n = grid.size();
		m = grid[0].size();
		
		int largestRegion = 0;
		for (int i = 0; i<n; i++) {
			for (int j = 0; j<m; j++) {
				if (grid[i][j] == 1) {
					int currSize = dfs(grid, i, j);
					largestRegion = max(largestRegion, currSize);
				}
			}
		}
		return largestRegion;
		
	}
};

//BFS
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMaxArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        vector<vector<int>> vis(n, vector<int>(m, 0));
        
        vector<pair<int, int>> dir = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0},
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };
        
        int maxi = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !vis[i][j]) {
                    int current_size = 1;
                    queue<pair<int, int>> q;

                    q.push({i, j});
                    vis[i][j] = 1;

                    while (!q.empty()) {
                        auto [a, b] = q.front();
                        q.pop();

                        for (auto& vec : dir) {
                            int x = a + vec.first;
                            int y = b + vec.second;

                            if (x >= 0 && y >= 0 && x < n && y < m && 
                                grid[x][y] == 1 && !vis[x][y]) {
                                vis[x][y] = 1; 
                                current_size++;
                                q.push({x, y});
                            }
                        }
                    }\
                    maxi = max(maxi, current_size);
                }
            }
        }

        return maxi;
    }
};
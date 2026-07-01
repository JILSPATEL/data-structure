class Solution {
public:
    bool isPossible(vector<vector<int>>& dist,int tar){
        int n=dist.size();
        if(dist[0][0]<tar){
            return false;
        }
        vector<vector<bool>> vis(n,vector<bool>(n,false));
        queue<pair<int,int>> q;
        q.push({0,0});
        vis[0][0]=true;
        vector<pair<int,int>> dir={{-1,0},{1,0},{0,-1},{0,1}};
        while(!q.empty()){
            auto curr=q.front();
            q.pop();
            int row=curr.first;
            int col=curr.second;
            if(row==n-1 && col==n-1) return true;
            for(auto vec:dir){
                int newRow=row+vec.first;
                int newCol=col+vec.second;
                if(newRow>=0 && newCol>=0 && newRow<n && newCol<n && !vis[newRow][newCol] && dist[newRow][newCol]>=tar){
                    q.push({newRow,newCol});
                    vis[newRow][newCol]=true;
                }
            }
        }
        return false;
    }
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return 0;
        }
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

        queue<pair<int, int>> q;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            int row = curr.first;
            int col = curr.second;

            for (int k = 0; k < 4; k++) {
                int newRow = row + dr[k];
                int newCol = col + dc[k];

                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n) {
                    int newDist = dist[row][col] + 1;

                    if (newDist < dist[newRow][newCol]) {
                        dist[newRow][newCol] = newDist;
                        q.push({newRow, newCol});
                    }
                }
            }
        }
        int low=0;
        int high=2*n;
        int ans=0;

        while(low<=high){
            int mid=low+(high-low)/2;
            if(isPossible(dist,mid)){
                ans=mid;
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return ans;
    }
};
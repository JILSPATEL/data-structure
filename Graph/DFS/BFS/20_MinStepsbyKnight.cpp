/*
Problem: Minimum steps by Knight

Description:
Given an N x N chessboard, a knight's start position and a target position (1-indexed),
find the minimum number of moves required for the knight to reach the target.

Intuition:
Each board cell is a node in an unweighted graph and knight moves are edges connecting nodes.
The shortest number of moves equals the shortest path length in this graph.

Approach:
Perform a Breadth-First Search (BFS) from the start cell, marking visited cells.
Each BFS level corresponds to one knight move; when the target is first reached,
the level is the minimum number of moves.
This implementation uses a priority_queue as a min-heap over distances (equivalent to BFS
when all edge weights are 1) and a visited matrix to avoid revisiting cells.

Example:
N = 6, knightPos = [4, 5], targetPos = [1, 1]
One shortest sequence of moves (1-indexed):
 (4,5) -> (2,4) -> (3,2) -> (1,1)
Answer: 3
*/
class Solution {
	public:
	int minStepToReachTarget(vector<int>& knightPos, vector<int>& targetPos, int n) {
		vector<pair<int, int>> dir = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
		int sRow = knightPos[0]-1;
		int sCol = knightPos[1]-1;
		int dRow = targetPos[0]-1;
		int dCol = targetPos[1]-1;
		vector<vector<int>> vis(n,vector<int>(n,0));
		priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
		pq.push({0, {sRow, sCol}});
		vis[sRow][sCol]=1;
		while (!pq.empty()) {
			auto curr=pq.top();
			pq.pop();
			int dist=curr.first;
			int row=curr.second.first;
			int col=curr.second.second;
			
			if(row==dRow && col==dCol){
			    return dist;
			}
			
			for(auto &vec:dir){
			    int x=row+vec.first;
			    int y=col+vec.second;
			    
			    if(x>=0 && x<n && y>=0 && y<n && !vis[x][y]){
			        pq.push({dist+1,{x,y}});
			        vis[x][y]=1;
			    }
			}
		}
		return -1;
	}
};

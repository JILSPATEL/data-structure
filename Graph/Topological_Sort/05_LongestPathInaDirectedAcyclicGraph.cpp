/*
Problem: Longest Path in a Directed Acyclic Graph (DAG)

Description:
Given a weighted directed acyclic graph with n nodes (0..n-1) and a source node `src`,
compute the longest distance from `src` to every other node. If a node is unreachable,
its distance should be treated as negative infinity (here represented by INT_MIN).

Approach (Topological Sort + Relaxation):
- Build adjacency list from edge list (u -> v with weight w).
- Compute a topological ordering of the DAG (using DFS finishing times / stack).
- Initialize all distances to `INT_MIN` and set `dist[src] = 0`.
- Process nodes in topological order; for each node with finite distance, relax
    all outgoing edges: dist[v] = max(dist[v], dist[u] + w).

Intuition:
In a topological order of a DAG, all edges go from earlier to later nodes. That
means when we process a node we have already computed the best possible distances
to it, so a single pass in that order correctly propagates longest-path values.

Example:
Nodes: 0..5
Edges: 0->1 (5), 0->2 (3), 1->3 (6), 2->3 (4), 2->4 (2), 3->4 (1), 4->5 (2)
Source: 0
Topological order (one valid): 0,1,2,3,4,5
Stepwise distances:
dist[0]=0
after edges from 0: dist[1]=5, dist[2]=3
after relaxing 1->3: dist[3]=11
after relaxing 2->3 and 2->4: dist[3]=11 (unchanged), dist[4]=5
after relaxing 3->4: dist[4]=12
after relaxing 4->5: dist[5]=14
Result: [0,5,3,11,12,14]

Time complexity: O(n + m) where m = number of edges (topological sort + single pass relax)
Space complexity: O(n + m) for adjacency list and stack
*/

class Solution {
  public:
    void topoSort(int node,vector<vector<pair<int,int>>> &adj,vector<int> &vis,stack<int> &st){
        vis[node]=1;
        for(auto &it:adj[node]){
            int neb=it.first;
            if(!vis[neb]){
                topoSort(neb,adj,vis,st);
            }
        }
        st.push(node);
    }
    vector<int> maxDistance(int n, int src, vector<vector<int>> &edges) {
        vector<vector<pair<int,int>>> adj(n);
        
        for(auto &edge:edges){
            int u=edge[0];
            int v=edge[1];
            int wt=edge[2];
            
            adj[u].push_back({v,wt});
        }
        vector<int> vis(n,0);
        stack<int> st;
        
        for(int i=0;i<n;i++){
            if(!vis[i]){
                topoSort(i,adj,vis,st);
            }
        }
        
        vector<int> dist(n,INT_MIN);
        
        dist[src]=0;
        
        while(!st.empty()){
            int node=st.top();
            st.pop();
            
            if(dist[node]!=INT_MIN){
                for(auto &it:adj[node]){
                    int neb=it.first;
                    int newWt=it.second;
                    
                    if(dist[node]+newWt>dist[neb]){
                        dist[neb]=dist[node]+newWt;
                    }
                }
            }
        }
        return dist;
    }
};
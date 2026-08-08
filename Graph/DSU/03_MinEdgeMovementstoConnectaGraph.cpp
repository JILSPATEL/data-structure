class DSU{
    public:
    vector<int> parent;
    vector<int> rank;
    DSU(int n){
        parent.resize(n);
        rank.resize(n,0);
        
        for(int i=0;i<n;i++){
            parent[i]=i;
        }
    }
    int find(int n){
        if(parent[n]!=n){
            parent[n]=find(parent[n]);
        }
        return parent[n];
    }
    void unionSet(int x,int y){
        int px = find(x);
        int py = find(y);
        if(px==py) return;
        
        if (px == py) return;

        if (rank[px] < rank[py]) {
            parent[px] = py;
        } 
        else if (rank[px] > rank[py]) {
            parent[py] = px;
        } 
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

class Solution {
  public:
    int minEdgesReq(int n, vector<vector<int>>& edges) {
        DSU dsu(n);
        if (edges.size() < n - 1) return -1;
        for(auto &edge:edges){
            dsu.unionSet(edge[0],edge[1]);
        }
        unordered_set<int> components;
        for(int i=0;i<n;i++){
            components.insert(dsu.find(i));
        }
        return components.size()-1;
    }
};
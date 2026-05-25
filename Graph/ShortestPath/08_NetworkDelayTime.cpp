/**
 * Problem: Network Delay Time
 *
 * Description:
 * Given directed weighted edges:
 *
 *      times[i]={u,v,w}
 *
 * Find the minimum time required for a signal
 * from source k to reach all nodes.
 *
 * If some node cannot be reached,
 * return -1.
 *
 * Approach: Dijkstra
 *
 * Idea:
 * - Nodes are graph vertices
 * - Edge weight = transmission time
 * - Find shortest time from source
 *   to all nodes
 * - Maximum distance among all nodes
 *   becomes answer
 *
 * Time Complexity:
 *      O((V+E)logV)
 *
 * Space Complexity:
 *      O(V+E)
 */

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        
        vector<vector<pair<int,int>>> adj(n+1);

        for(auto &it:times){
            adj[it[0]].push_back({it[1],it[2]});
        }

        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<>
        > pq;

        vector<int> dist(n+1,INT_MAX);

        dist[k]=0;
        pq.push({0,k});

        while(!pq.empty()){

            auto curr=pq.top();
            pq.pop();

            int cost=curr.first;
            int node=curr.second;

            if(cost>dist[node])
                continue;

            for(auto &neb:adj[node]){

                int newNode=neb.first;
                int wt=neb.second;

                if(cost+wt<dist[newNode]){

                    dist[newNode]=cost+wt;

                    pq.push(
                        {
                            cost+wt,
                            newNode
                        }
                    );
                }
            }
        }

        int ans=0;

        // <= instead of <
        for(int i=1;i<=n;i++){

            if(dist[i]==INT_MAX)
                return -1;

            ans=max(ans,dist[i]);
        }

        return ans;
    }
};

// Bfs approach

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n+1);

        for(auto &it:times){
            adj[it[0]].push_back({it[1],it[2]});
        }

        vector<int> dist(n+1,INT_MAX);

        queue<pair<int,int>> q;

        q.push({k,0});
        dist[k]=0;

        while(!q.empty()){
            auto curr=q.front();
            q.pop();

            int node=curr.first;
            int cost=curr.second;

            for(auto &neb:adj[node]){
                int newNode=neb.first;
                int wt=neb.second;

                int newCost=cost+wt;
                if(newCost<dist[newNode]){
                    dist[newNode]=newCost;
                    q.push({newNode,newCost});
                }
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            if(dist[i]==INT_MAX){
                return -1;
            }
            ans=max(ans,dist[i]);
        }
        return ans;
    }
};
/*
Problem Statement:
Given an array of equations of the form "a==b" or "a!=b" using lowercase letters,
we need to determine whether it is possible to assign truth values to all variables
so that every equality equation holds and every inequality equation is satisfied.

Example:
Input: ["a==b", "b!=c", "c==a"]
Output: false
Explanation: From a==b and c==a, we get a, b, and c in the same group, so b!=c is impossible.

Intuition:
If two variables are connected by "==", they must belong to the same group.
If two variables are connected by "!=", they must belong to different groups.
So we can model this using Disjoint Set Union (DSU/Union-Find).

Approach:
1. First, union all variables that appear in equality equations.
2. Then, scan the inequality equations and check whether the two variables
   already belong to the same set. If they do, the condition is impossible.
3. If no contradiction is found, return true.
*/

class DSU{
    public: 
        vector<int> parent;
        vector<int> size;

        DSU(int n){
            parent.resize(n);
            size.resize(n,1);
            for(int i=0;i<n;i++){
                parent[i]=i;
            }
        }

        int find(int node){
            if(parent[node]==node){
                return node;
            }

            return parent[node]=find(parent[node]);
        }

        void unionSet(int u,int v){
            int pu=find(u);
            int pv=find(v);

            if(pu==pv) return;
            else if(size[pu]<size[pv]){
                parent[pu]=pv;
                size[pv]+=size[pu];
            }else{
                parent[pv]=pu;
                size[pu]+=size[pv];
            }
        }
};

class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        DSU dsu(26);

        for(string &s:equations){
            if(s[1]=='='){
                dsu.unionSet(s[0]-'a',s[3]-'a');
            }
        }
        for(string &s:equations){
            if(s[1]=='!'){
                char first=s[0]-'a';
                char second=s[3]-'a';
                int pf=dsu.find(first);
                int ps=dsu.find(second);

                if(pf==ps) return false;
            }
        }
        return true;

    }
};
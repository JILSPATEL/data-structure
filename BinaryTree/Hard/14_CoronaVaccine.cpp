/*
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int x){
        data = x;
        left = right = NULL;
    }
};
*/

/*
Description:
We are given a binary tree and need to place the minimum number of vaccines so that every node is covered.
A node is considered covered if it itself has a vaccine, or if its parent/child has a vaccine.
The goal is to minimize the total number of vaccine doses.

Intuition:
This is a tree DP problem. For every node, we need to decide what is the best choice based on the
status of its parent and children. A naive greedy choice fails because a decision at one node affects
its parent and children. So we calculate the minimum cost for each node under different states.

Approach:
We define a DP for each node and state:
- 0: the node is uncovered and must be vaccinated
- 1: the node has a vaccine
- 2: the node is covered by a child, so it does not need a vaccine

For each node, we evaluate the best valid combination of choices for its left and right subtrees and
select the minimum cost.

Example:
Consider this tree:
        1
       / \
      2   3
     / \
    4   5

One optimal solution is to vaccinate nodes 1 and 4, and the total is 2 vaccines.
The DP computes this by checking every valid state combination for each subtree and taking the minimum.

This is a classic tree-state optimization problem where each node has only a few valid possibilities,
so the total complexity is O(n).
*/
class Solution {
  public:
    int dfs(Node* root, int state, unordered_map<Node*, vector<int>>& dp){
        if(!root) return 0;
        if(dp.find(root)==dp.end()){
            dp[root]={-1,-1,-1};
        }
        if(dp[root][state]!=-1) return dp[root][state];
        int res=0;
        
        if(state==0){
            res=1+dfs(root->left,1,dp)+dfs(root->right,1,dp);
        }else if(state==1){
            int take = 1 + dfs(root->left, 1, dp) + dfs(root->right, 1, dp); 
            int notTake = dfs(root->left, 2, dp) + dfs(root->right, 2, dp);
            res=min(take,notTake);
        }else{
            int take=1+dfs(root->left,1,dp)+dfs(root->right,1,dp);
            int notTake=INT_MAX;
            if (root->left) 
                notTake = min(notTake, dfs(root->left, 0, dp) + dfs(root->right, 2, dp));
            if (root->right) 
                notTake = min(notTake, dfs(root->left, 2, dp) + dfs(root->right, 0, dp));

            res = min(take, notTake);
        }
        return dp[root][state]=res;
    }
    int supplyVaccine(Node* root) {
        unordered_map<Node*, vector<int>> dp;
        return dfs(root,2,dp);
    }
};
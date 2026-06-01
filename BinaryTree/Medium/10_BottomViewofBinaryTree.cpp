/**
 * Bottom View of Binary Tree
 *
 * Approach:
 * - Perform BFS (Level Order Traversal).
 * - Assign a horizontal distance (column) to each node.
 * - For every column, keep updating the node value.
 * - The last node encountered for a column becomes part of
 *   the bottom view.
 *
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 */

class Solution {
  public:
    vector<int> bottomView(Node *root) {
        // code here
        map<int,int> mp;
        queue<pair<Node*,int>>q;
        mp[0]=root->data;
        q.push({root,0});
        vector<int> res;
        
        while(!q.empty()){
            auto curr=q.front();
            q.pop();
            
            Node* node=curr.first;
            int col=curr.second;
            
            mp[col]=node->data;
            
            if(node->left) q.push({node->left,col-1});
            if(node->right) q.push({node->right,col+1});
        }
        for(auto &it:mp){
            res.push_back(it.second);
        }
        return res;
    }
};
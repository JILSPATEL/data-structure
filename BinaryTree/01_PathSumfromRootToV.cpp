/*
The sum of the values of the nodes on the unique path from the
root of T to v.

Time Complexity:
O(n) to build tree.
O(n) to find path.

Space Complexity:
O(n) for tree + queue.
O(h) for recursion stack (h = tree height)
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v):val(v),left(nullptr),right(nullptr){}
};

// Build binary tree from level-order input with "N" as null
Node* buildTree(vector<string>& arr){
    if(arr.empty() || arr[0]=="N") return nullptr;
    Node* root = new Node(stoi(arr[0]));
    queue<Node*> q;
    q.push(root);
    int i=1;
    while(!q.empty() && i<arr.size()){
        Node* curr = q.front(); q.pop();
        if(i<arr.size() && arr[i]!="N"){
            curr->left = new Node(stoi(arr[i]));
            q.push(curr->left);
        }
        i++;
        if(i<arr.size() && arr[i]!="N"){
            curr->right = new Node(stoi(arr[i]));
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

// DFS to calculate path sum from root to node with value v
int pathSumDFS(Node* root, int v, int currSum){
    if(!root) return -1; // -1 means node not found in this path
    currSum += root->val;
    if(root->val == v) return currSum;
    int left = pathSumDFS(root->left, v, currSum);
    if(left != -1) return left;
    return pathSumDFS(root->right, v, currSum);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    vector<string> arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    Node* root = buildTree(arr);

    int v; cin>>v;
    int sum = pathSumDFS(root, v, 0);
    if(sum != -1) cout<<sum<<"\n";
    else cout<<"Node not found\n";
}

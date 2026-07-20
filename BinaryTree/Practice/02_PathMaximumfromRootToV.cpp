/*
 The maximum value among the nodes on the unique path from the
root of T to v.
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

// DFS to find maximum value along path from root to node with value v
int pathMaxDFS(Node* root, int v, int currMax){
    if(!root) return INT_MIN; // not found
    currMax = max(currMax, root->val);
    if(root->val == v) return currMax;
    int left = pathMaxDFS(root->left, v, currMax);
    if(left != INT_MIN) return left;
    return pathMaxDFS(root->right, v, currMax);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    vector<string> arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    Node* root = buildTree(arr);

    int v; cin>>v;
    int mx = pathMaxDFS(root, v, INT_MIN);
    if(mx != INT_MIN) cout<<mx<<"\n";
    else cout<<"Node not found\n";
}

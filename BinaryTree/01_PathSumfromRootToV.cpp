/*
The sum of the values of the nodes on the unique path from the
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
        // left child
        if(i<arr.size() && arr[i]!="N"){
            curr->left = new Node(stoi(arr[i]));
            q.push(curr->left);
        }
        i++;
        // right child
        if(i<arr.size() && arr[i]!="N"){
            curr->right = new Node(stoi(arr[i]));
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

// Find path sum from root to node with value v
bool findPath(Node* root,int v,vector<int>& path){
    if(!root) return false;
    path.push_back(root->val);
    if(root->val==v) return true;
    if(findPath(root->left,v,path) || findPath(root->right,v,path)) return true;
    path.pop_back();
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    vector<string> arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    Node* root = buildTree(arr);

    int v; cin>>v;
    vector<int> path;
    if(findPath(root,v,path)){
        int sum=0;
        for(int x:path) sum+=x;
        cout<<sum<<"\n";
    } else cout<<"Node not found\n";
}

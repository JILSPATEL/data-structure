/*
 The weight of the shortest path from v to any leaf node in T.
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(NULL), right(NULL) {}
};

Node* buildTree(vector<string>& arr) {
    if (arr.empty() || arr[0] == "N") return NULL;

    Node* root = new Node(stoi(arr[0]));
    queue<Node*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < (int)arr.size()) {
        Node* curr = q.front();
        q.pop();

        if (i < (int)arr.size() && arr[i] != "N") {
            curr->left = new Node(stoi(arr[i]));
            q.push(curr->left);
        }
        i++;

        if (i < (int)arr.size() && arr[i] != "N") {
            curr->right = new Node(stoi(arr[i]));
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

Node* findNode(Node* root, int v) {
    if (!root) return NULL;
    if (root->val == v) return root;
    Node* L = findNode(root->left, v);
    if (L) return L;
    return findNode(root->right, v);
}

int shortestToLeaf(Node* src) {
    queue<pair<Node*, int>> q;
    q.push({src, src->val});
    unordered_set<Node*> vis;
    vis.insert(src);
    int ans = INT_MAX;

    while (!q.empty()) {
        auto [u, w] = q.front();
        q.pop();
        if (!u->left && !u->right) ans = min(ans, w);
        if (u->left && !vis.count(u->left)) {
            q.push({u->left, w + u->left->val});
            vis.insert(u->left);
        }
        if (u->right && !vis.count(u->right)) {
            q.push({u->right, w + u->right->val});
            vis.insert(u->right);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    Node* root = buildTree(arr);

    int v;
    cin >> v;

    Node* target = findNode(root, v);
    if (!target)
        cout << "Node not found\n";
    else
        cout << shortestToLeaf(target) << "\n";

    return 0;
}

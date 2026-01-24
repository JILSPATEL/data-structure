#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

Node* buildTreeFromPairs(int n) {
    if (n == 0) return nullptr;

    map<int, Node*> nodes;
    set<int> children;

    for (int i = 0; i < n-1; i++) {
        int parent, child;
        cin >> parent >> child;

        if (!nodes[parent]) nodes[parent] = new Node(parent);
        if (!nodes[child]) nodes[child] = new Node(child);

        children.insert(child);

        Node* p = nodes[parent];
        if (!p->left) p->left = nodes[child];
        else p->right = nodes[child];
    }

    for (auto &it : nodes) {
        if (!children.count(it.first)) return it.second;
    }
    return nodes.begin()->second; 
}

bool collectPath(Node* root, int v, vector<int>& path) {
    if (!root) return false;
    path.push_back(root->val);
    if (root->val == v) return true;
    if (collectPath(root->left, v, path) || collectPath(root->right, v, path))
        return true;
    path.pop_back();
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Node* root = buildTreeFromPairs(n);

    int v, k;
    cin >> v >> k;

    vector<int> path;
    collectPath(root, v, path);

    sort(path.begin(), path.end());  
    cout << path[k - 1] << "\n";

    return 0;
}

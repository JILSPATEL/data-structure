#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v): val(v), left(nullptr), right(nullptr) {}
};

Node* buildTreeFromPairs(int n) {
    if (n == 0) return nullptr;

    map<int, Node*> nodes;
    set<int> children;

    for (int i = 0; i < n-1; ++i) {
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
    return nodes.begin()->second; // fallback
}

int pathMaxDFS(Node* root, int v, int currMax) {
    if (!root) return INT_MIN;

    currMax = max(currMax, root->val);
    if (root->val == v) return currMax;

    int leftResult = pathMaxDFS(root->left, v, currMax);
    if (leftResult != INT_MIN) return leftResult;

    return pathMaxDFS(root->right, v, currMax);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Node* root = buildTreeFromPairs(n);

    int v;
    cin >> v;

    int mx = pathMaxDFS(root, v, INT_MIN);
    cout << mx << "\n";

    return 0;
}

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

Node* findNode(Node* root, int v) {
    if (!root) return nullptr;
    if (root->val == v) return root;
    Node* L = findNode(root->left, v);
    if (L) return L;
    return findNode(root->right, v);
}

void collect(Node* root, vector<int>& nodes) {
    if (!root) return;
    nodes.push_back(root->val);
    collect(root->left, nodes);
    collect(root->right, nodes);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Node* root = buildTreeFromPairs(n);

    int v;
    cin >> v;        // target node
    int k;
    cin >> k;        // k in new line

    Node* target = findNode(root, v);

    vector<int> nodes;
    collect(target, nodes);
    sort(nodes.begin(), nodes.end());
    cout << nodes[k - 1] << "\n";

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

unordered_map<int, Node*> mp;

Node* getNode(int v) {
    if (mp.count(v)) return mp[v];
    mp[v] = new Node(v);
    return mp[v];
}

Node* buildTreeFromEdges(int n) {
    Node* root = nullptr;
    unordered_set<int> childSet;

    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        Node* parent = getNode(u);
        Node* child = getNode(v);

        if (!parent->left) parent->left = child;
        else parent->right = child;

        childSet.insert(v);
        if (!root) root = parent; 
    }

    for (auto& p : mp) {
        if (!childSet.count(p.first)) {
            root = p.second;
            break;
        }
    }
    return root;
}

Node* findNode(Node* root, int v) {
    if (!root) return nullptr;
    if (root->val == v) return root;
    Node* L = findNode(root->left, v);
    if (L) return L;
    return findNode(root->right, v);
}

int subtreeSum(Node* root) {
    if (!root) return 0;
    return root->val + subtreeSum(root->left) + subtreeSum(root->right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Node* root = buildTreeFromEdges(n);

    int v;
    cin >> v;

    Node* target = findNode(root, v);
    cout << subtreeSum(target) << "\n";

    return 0;
}

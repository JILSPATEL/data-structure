#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(NULL), right(NULL) {}
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

        Node* p = nodes[parent];
        if (!p->left) p->left = nodes[child];
        else p->right = nodes[child];

        children.insert(child);
    }

    for (auto &it : nodes) {
        if (!children.count(it.first)) return it.second;
    }
    return nodes.begin()->second;
}

Node* findNode(Node* root, int v) {
    if (!root) return NULL;
    if (root->val == v) return root;
    Node* L = findNode(root->left, v);
    if (L) return L;
    return findNode(root->right, v);
}

int shortestToLeaf(Node* src) {
    queue< pair<Node*, int> > q;
    unordered_set<Node*> vis;
    q.push(make_pair(src, src->val));
    vis.insert(src);
    int ans = INT_MAX;

    while (!q.empty()) {
        pair<Node*, int> p = q.front(); q.pop();
        Node* u = p.first;
        int w = p.second;

        if (!u->left && !u->right) ans = min(ans, w);

        if (u->left && !vis.count(u->left)) {
            vis.insert(u->left);
            q.push(make_pair(u->left, w + u->left->val));
        }
        if (u->right && !vis.count(u->right)) {
            vis.insert(u->right);
            q.push(make_pair(u->right, w + u->right->val));
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Node* root = buildTreeFromPairs(n);

    int v;
    cin >> v;

    Node* target = findNode(root, v);
    if (!target)
        cout << "Node not found\n";
    else
        cout << shortestToLeaf(target) << "\n";

    return 0;
}

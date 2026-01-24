#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Build tree from n vertices and n-1 edges
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

// DFS to find target node
Node* findNode(Node* root, int v) {
    if (!root) return nullptr;
    if (root->val == v) return root;
    Node* L = findNode(root->left, v);
    if (L) return L;
    return findNode(root->right, v);
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

    // BFS to parent map to treat tree as undirected
    map<Node*, Node*> parentMap;
    queue<Node*> q;
    q.push(root);
    parentMap[root] = nullptr;

    while (!q.empty()) {
        Node* u = q.front(); q.pop();
        if (u->left) { parentMap[u->left] = u; q.push(u->left); }
        if (u->right) { parentMap[u->right] = u; q.push(u->right); }
    }

    // BFS from target to compute min path sum to any other node
    queue< pair<Node*, int> > bfs;
    unordered_set<Node*> vis;
    bfs.push(make_pair(target, target->val));
    vis.insert(target);
    int minSum = INT_MAX;

    while (!bfs.empty()) {
        pair<Node*, int> p = bfs.front(); bfs.pop();
        Node* node = p.first;
        int sum = p.second;

        if (node != target) minSum = min(minSum, sum);

        if (node->left && !vis.count(node->left)) {
            vis.insert(node->left);
            bfs.push(make_pair(node->left, sum + node->left->val));
        }
        if (node->right && !vis.count(node->right)) {
            vis.insert(node->right);
            bfs.push(make_pair(node->right, sum + node->right->val));
        }
        if (parentMap[node] && !vis.count(parentMap[node])) {
            vis.insert(parentMap[node]);
            bfs.push(make_pair(parentMap[node], sum + parentMap[node]->val));
        }
    }

    cout << minSum << "\n";

    return 0;
}

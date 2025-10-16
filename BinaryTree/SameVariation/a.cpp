#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

int pathSumDFS(Node* root, int v, int currSum) {
    if (!root) return -1;
    currSum += root->val;
    if (root->val == v) return currSum;

    int left_sum = pathSumDFS(root->left, v, currSum);
    if (left_sum != -1) return left_sum;
    return pathSumDFS(root->right, v, currSum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<int, vector<int>> adj;
    unordered_set<int> children;

    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        children.insert(v);
    }

    int rootVal = -1;
    for (auto &p : adj) {
        if (!children.count(p.first)) {
            rootVal = p.first;
            break;
        }
    }
    if (rootVal == -1) rootVal = adj.begin()->first;

    map<int, Node*> nodeMap;
    map<int, bool> visited;
    queue<int> q;
    q.push(rootVal);
    nodeMap[rootVal] = new Node(rootVal);
    visited[rootVal] = true;

    while (!q.empty()) {
        int u_val = q.front();
        q.pop();

        Node* u_node = nodeMap[u_val];
        for (int v_val : adj[u_val]) {
            if (!visited[v_val]) {
                visited[v_val] = true;
                Node* v_node = new Node(v_val);
                nodeMap[v_val] = v_node;

                if (!u_node->left) u_node->left = v_node;
                else u_node->right = v_node;

                q.push(v_val);
            }
        }
    }

    int v_target;
    cin >> v_target;

    int sum = pathSumDFS(nodeMap[rootVal], v_target, 0);
    cout << sum << "\n";

    return 0;
}

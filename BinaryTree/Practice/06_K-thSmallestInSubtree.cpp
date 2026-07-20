/*
Given an integer k, the element of rank k among the values of the
nodes in the subtree rooted at v.
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

    vector<string> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    Node* root = buildTree(arr);

    int v, k;
    cin >> v >> k;

    Node* target = findNode(root, v);
    if (!target) {
        cout << "Node not found\n";
    } else {
        vector<int> nodes;
        collect(target, nodes);
        sort(nodes.begin(), nodes.end());
        if (k <= (int)nodes.size())
            cout << nodes[k - 1] << "\n";
        else
            cout << "Invalid k\n";
    }

    return 0;
}

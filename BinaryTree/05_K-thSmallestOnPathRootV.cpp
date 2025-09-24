/*
Given an integer k, the element of rank k among the values of the
nodes on the unique path from the root of T to v.
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

bool collectPath(Node* root, int v, vector<int>& path) {
    if (!root) return false;
    path.push_back(root->val);
    if (root->val == v) return true;
    if (collectPath(root->left, v, path) || collectPath(root->right, v, path)) return true;
    path.pop_back();
    return false;
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

    vector<int> path;
    if (collectPath(root, v, path)) {
        sort(path.begin(), path.end());
        if (k <= (int)path.size())
            cout << path[k - 1] << "\n";
        else
            cout << "Invalid k\n";
    } else {
        cout << "Node not found\n";
    }

    return 0;
}

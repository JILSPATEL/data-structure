/* Structure of Binary Tree Node
class Node {
    public:
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};
*/

/*
Intuition:
- A turn happens only when the direction of movement changes while moving from one node to another.
- For example, if we move from a node to its left child and later from the parent to its right child, the path changed direction and a turn is added.
- So the problem becomes: find the path from p to q, and count how many times the movement direction changes along that path.

Approach:
1. Build a graph from the tree where each edge stores the direction of movement:
   - DL = Down-Left
   - DR = Down-Right
   - UR = Up-Right
   - UL = Up-Left
2. Run DFS from p to q while preventing revisits to the parent node.
3. As we explore the route, compare the current direction with the previous one.
4. If the direction changes, increment the turn count.
5. Return the total turns; if no valid path exists, return -1.

Example:
Tree:
        5
       / \
      2   8
     / \   \
    1   3   9

From 1 to 9:
- 1 -> 2 : UR
- 2 -> 5 : UR
- 5 -> 8 : DR
- 8 -> 9 : DR

The direction changes once: UR -> DR, so the answer is 1.
This is exactly what the DFS checks while traversing from p to q.
*/

class Solution {
public:
    const int DL = 1; // Down-Left
    const int DR = 2; // Down-Right
    const int UR = 3; // Up-Right
    const int UL = 4; // Up-Left

    unordered_map<int, vector<pair<int, int>>> adj;

    void buildGraph(Node* root) {
        if (!root)
            return;

        if (root->left) {
            adj[root->data].push_back({root->left->data, DL});
            adj[root->left->data].push_back({root->data, UR});
            buildGraph(root->left);
        }

        if (root->right) {
            adj[root->data].push_back({root->right->data, DR});
            adj[root->right->data].push_back({root->data, UL});
            buildGraph(root->right);
        }
    }

    int dfs(int curr, int dest, int parent, int prevDir) {
        if (curr == dest) {
            return 0;
        }

        for (auto& edge : adj[curr]) {

            int neb = edge.first;
            int direction = edge.second;

            if (neb == parent)
                continue;

            int turns = dfs(neb, dest, curr, direction);

            if (turns != -1) {

                // Direction changed => one turn
                if (prevDir != 0 && prevDir != direction) {
                    turns++;
                }

                return turns;
            }
        }

        return -1;
    }

    int numberOfTurns(Node* root, int p, int q) {

        if (!root)
            return -1;

        adj.clear();
        buildGraph(root);
        int ans=dfs(p, q, -1, 0);
        if(ans==0){
            return -1;
        }
        return ans;
    }
};
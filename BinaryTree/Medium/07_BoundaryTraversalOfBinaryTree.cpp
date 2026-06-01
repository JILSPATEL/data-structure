/**
 * Problem: Boundary Traversal of Binary Tree
 *
 * Boundary Traversal Order:
 * 1. Root Node
 * 2. Left Boundary (excluding leaf nodes)
 * 3. All Leaf Nodes (left to right)
 * 4. Right Boundary (excluding leaf nodes, in reverse order)
 *
 * Approaches:
 * 1. Recursive Traversal
 *    - Traverse left boundary.
 *    - Collect all leaf nodes.
 *    - Traverse right boundary and reverse it.
 *
 * 2. Iterative Boundary Traversal (Used Below)
 *    - Iteratively collect left boundary.
 *    - Recursively collect leaf nodes.
 *    - Iteratively collect right boundary and append in reverse.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H)
 * where:
 * N = Number of nodes
 * H = Height of tree (recursive stack)
 */

/*
Definition for Node

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};
*/

class Solution {
public:

    /**
     * Checks whether a node is a leaf node.
     */
    bool isLeaf(Node* root) {
        return !root->left && !root->right;
    }

    /**
     * Adds the left boundary nodes.
     * Excludes leaf nodes.
     */
    void leftBoundary(Node* root, vector<int>& res) {

        Node* curr = root->left;

        while (curr) {

            if (!isLeaf(curr))
                res.push_back(curr->data);

            if (curr->left)
                curr = curr->left;
            else
                curr = curr->right;
        }
    }

    /**
     * Adds all leaf nodes from left to right.
     */
    void addLeaves(Node* root, vector<int>& res) {

        if (!root)
            return;

        if (isLeaf(root)) {
            res.push_back(root->data);
            return;
        }

        addLeaves(root->left, res);
        addLeaves(root->right, res);
    }

    /**
     * Adds the right boundary nodes.
     * Excludes leaf nodes and stores them
     * in reverse order.
     */
    void rightBoundary(Node* root, vector<int>& res) {

        Node* curr = root->right;
        vector<int> temp;

        while (curr) {

            if (!isLeaf(curr))
                temp.push_back(curr->data);

            if (curr->right)
                curr = curr->right;
            else
                curr = curr->left;
        }

        for (int i = temp.size() - 1; i >= 0; i--) {
            res.push_back(temp[i]);
        }
    }

    vector<int> boundaryTraversal(Node* root) {

        vector<int> res;

        if (!root)
            return res;

        // Add root only if it is not a leaf
        if (!isLeaf(root))
            res.push_back(root->data);

        // 1. Left Boundary
        leftBoundary(root, res);

        // 2. Leaf Nodes
        addLeaves(root, res);

        // 3. Right Boundary (reversed)
        rightBoundary(root, res);

        return res;
    }
};
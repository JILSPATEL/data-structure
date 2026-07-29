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
};*/

/*
Intuition:
We can rebuild the tree if we know the preorder traversal and the preorder traversal of the mirror tree.
The first value in preorder is always the root. Once we know the root, we can find the position of the next
node in the mirror preorder to decide how much of the tree belongs to the left subtree and how much belongs to the right subtree.

Approach:
1. Use a global index `preIndex` to traverse the preorder array.
2. Store the positions of values from the mirror preorder in a hash map.
3. Recursively build the tree:
   - The current node is taken from preorder.
   - Find the index of the next preorder value in the mirror preorder to split the left and right subtrees.
   - Recurse on the left subtree with the correct range and then on the right subtree.
4. Return the root of the constructed tree.

Example:
pre = [1, 2, 4, 5, 3]
preMirror = [1, 3, 5, 4, 2]

The root is 1. The next value 2 belongs to the left subtree, and 3 belongs to the right subtree.
This helps us split the tree correctly while rebuilding it.
*/

class Solution {
  public:
    int preIndex;
    unordered_map<int, int> pos;
    
    Node *build(vector<int> &pre,vector<int> &preMirror,int l,int r){
        if(preIndex>=pre.size() || l>r){
            return nullptr;
        }
        
        Node* root=new Node(pre[preIndex++]);
        
        if (l == r || preIndex >= pre.size())
            return root;
            
        int idx=pos[pre[preIndex]];
        
        root->left=build(pre,preMirror,idx,r);
        root->right=build(pre,preMirror,l+1,idx-1);
        
        return root;
    }
    
    Node *constructBinaryTree(vector<int> &pre, vector<int> &preMirror) {
        preIndex=0;
        for(int i=0;i<preMirror.size();i++){
            pos[preMirror[i]]=i;
        }
        return build(pre,preMirror,0,preMirror.size()-1);
    }
};
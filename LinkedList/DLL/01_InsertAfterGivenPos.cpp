/**
 * Problem: Insert After p-th Node in Doubly Linked List
 *
 * Description:
 * Given head, position p (0-based), and value x,
 * insert a new node with value x AFTER the p-th node.
 *
 * Intuition:
 * Reach the p-th node, then insert new node after it.
 *
 * Approach (Your Logic):
 * 1. Traverse till p-th node using curr
 * 2. Insert new_Node after curr
 * 3. Update next and prev pointers
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

/*
class Node {
  public:
    int data;
    Node* next;
    Node* prev;

    Node(int x) {
        data = x;
        next = prev = nullptr;
    }
};
*/

class Solution {
  public:
    Node* insertAtPos(Node* head, int p, int x) {

        Node* curr = head;
        int count = 0;

        // Traverse till p-th node
        while (curr != nullptr && count < p) {
            curr = curr->next;
            count++;
        }

        // Create new node
        Node* new_Node = new Node(x);

        // Insert after curr
        if (curr != nullptr) {
            new_Node->next = curr->next;
            new_Node->prev = curr;

            if (curr->next != nullptr) {
                curr->next->prev = new_Node;
            }

            curr->next = new_Node;
        }

        return head;
    }
};
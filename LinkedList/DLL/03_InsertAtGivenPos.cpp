/**
 * Problem: Insert at Given Position in Doubly Linked List
 *
 * Description:
 * Insert a node with value x at position p (0-based indexing)
 * in a doubly linked list.
 *
 * Intuition:
 * To insert at position p, we must reach (p-1)th node,
 * then insert the new node after it.
 *
 * Approach (Your Logic):
 * 1. Traverse till (p-1) using curr pointer
 * 2. Insert new_Node after curr
 * 3. Update next and prev pointers carefully
 *
 * Edge Case:
 * - If p == 0 → insert at head
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
        Node* new_Node = new Node(x);

        // Case 1: Insert at head
        if (p == 0) {
            new_Node->next = head;
            if (head != nullptr) head->prev = new_Node;
            return new_Node;
        }

        // Traverse till (p-1)
        while (curr != nullptr && count < p - 1) {
            curr = curr->next;
            count++;
        }

        // Insert after curr
        if (curr != nullptr) {
            new_Node->next = curr->next;
            new_Node->prev = curr;

            if (new_Node->next != nullptr) {
                new_Node->next->prev = new_Node;
            }

            curr->next = new_Node;
        }

        return head;
    }
};
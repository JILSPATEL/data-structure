/**
 * Problem: Insert Node Before a Given Key in Doubly Linked List
 *
 * Description:
 * Given the head of a doubly linked list, a key, and a value,
 * insert a new node with value new_data BEFORE the node containing key.
 *
 * Intuition:
 * First find the node with the given key,
 * then insert the new node just before it.
 *
 * Approach (Your Logic):
 * 1. Traverse the list to find the node with given key
 * 2. If key not found → return head
 * 3. Create new node
 * 4. Link new node between (curr->prev) and curr
 * 5. Handle special case when inserting before head
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
    Node *insertBefore(Node *head, int key, int new_data) {

        Node *curr = head;

        // Step 1: Find the key
        while (curr != NULL) {
            if (curr->data == key)
                break;
            curr = curr->next;
        }

        // Step 2: If key not found
        if (curr == NULL)
            return head;

        // Step 3: Create new node
        Node *new_node = new Node(new_data);

        // Step 4: Link new node
        new_node->prev = curr->prev;
        new_node->next = curr;

        // Step 5: Fix previous node
        if (curr->prev != NULL) {
            curr->prev->next = new_node;
        } else {
            // inserting before head
            head = new_node;
        }

        // Step 6: Fix current node
        curr->prev = new_node;

        return head;
    }
};
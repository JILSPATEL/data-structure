/**
 * Problem: Insert Node at Front of Doubly Linked List
 *
 * Description:
 * Given the head of a doubly linked list and a value,
 * insert a new node at the beginning and return the new head.
 *
 * Intuition:
 * New node becomes the new head.
 * Link it with the old head.
 *
 * Approach:
 * 1. Create a new node
 * 2. Point new_node->next to current head
 * 3. Update head->prev to new_node (if head exists)
 * 4. Return new_node as new head
 *
 * Edge Case:
 * - If list is empty (head == NULL), new node is the only node
 *
 * Time Complexity: O(1)
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
    Node* insertAtFront(Node* head, int new_data) {

        // Step 1: Create new node
        Node* new_node = new Node(new_data);

        // Step 2: Link new node to current head
        new_node->next = head;

        // Step 3: Update previous pointer of head
        if (head != nullptr)
            head->prev = new_node;

        // Step 4: Return new node as new head
        return new_node;
    }
};
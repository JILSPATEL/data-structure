/**
 * Problem: Search in a Linked List
 *
 * Description:
 * Given the head of a singly linked list and a key,
 * check whether the key exists in the linked list.
 *
 * Intuition:
 * Traverse the list node by node and compare each value with the key.
 *
 * Approach (Linear Search - Used here):
 * 1. Start from head
 * 2. Traverse each node:
 *      - If node->data == key → return true
 * 3. If end is reached → return false
 *
 * Alternative Approaches:
 *
 * 1. Iterative (Used here):
 *    - Simple traversal
 *    - Most efficient for linked list
 *
 * 2. Recursive Approach:
 *    - Check current node, then recursively search in next
 *
 * Time Complexity:
 * - O(n) → In worst case, traverse entire list
 *
 * Space Complexity:
 * - O(1) → No extra space used
 */

/*
class Node {
  public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
*/

class Solution {
  public:
    bool searchKey(Node* head, int key) {
        Node* temp = head;

        // Traverse the linked list
        while (temp) {
            if (temp->data == key) {
                return true;
            }
            temp = temp->next;
        }

        return false;
    }
};
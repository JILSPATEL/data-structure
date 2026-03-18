/**
 * Problem: Reverse a Doubly Linked List
 * 
 * Description:
 * Given the head of a doubly linked list, reverse the list and return the new head.
 * Each node contains:
 *   - next pointer → forward link
 *   - prev pointer → backward link
 * 
 * Approaches:
 * 
 * 1. Iterative Pointer Swap (Optimal)
 *    - Traverse the list using a pointer `curr`
 *    - For every node:
 *        swap(next, prev)
 *    - Move forward using original next (stored in temp)
 *    - Keep updating head to current node
 * 
 *    Why it works:
 *    - Reversing DLL is just swapping links since both directions exist
 * 
 * 2. Recursive Approach (Alternative)
 *    - Swap pointers and recurse for next node
 *    - Less preferred due to stack usage
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

class Solution {
public:
    Node* reverse(Node* head) {

        // Edge case: empty or single node
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        Node* curr = head;

        // Traverse and swap next & prev
        while (curr) {

            Node* temp = curr->next;

            // Swap pointers
            curr->next = curr->prev;
            curr->prev = temp;

            // Update head to current node
            head = curr;

            // Move to next node (original next)
            curr = temp;
        }

        return head;
    }
};
/**
 * Length of Loop in Linked List
 * --------------------------------
 * Given a linked list, detect if a cycle exists.
 * If yes, return the length of the loop.
 * Otherwise, return 0.
 *
 * Approaches:
 *
 * 1. Floyd’s Cycle Detection (Tortoise & Hare) (Used Here)
 *    - Use two pointers: slow (1 step) and fast (2 steps)
 *    - If they meet → cycle exists
 *    - Then traverse the loop once to calculate its length
 *
 * 2. Hashing Approach
 *    - Store visited nodes in a set/map
 *    - When a node repeats → cycle found
 *    - Count nodes in cycle
 *    - Space: O(N)
 *
 * ⏱ Time Complexity: O(N)
 * 🗂 Space Complexity: O(1)
 */

class Solution {
public:
    int lengthOfLoop(Node *head) {
        Node* slow = head;
        Node* fast = head;

        // Step 1: Detect cycle using Floyd’s algorithm
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            // Cycle detected
            if (slow == fast) {
                int len = 1;

                // Step 2: Count loop length
                Node* temp = slow->next;
                while (temp != slow) {
                    temp = temp->next;
                    len++;
                }

                return len;
            }
        }

        // No cycle
        return 0;
    }
};
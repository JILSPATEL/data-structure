/**
 * 🔁 Find Start of Cycle in Linked List
 * -------------------------------------
 * Given the head of a linked list, return the data value of the node
 * where the cycle begins. If no cycle exists, return -1.
 *
 * Approach:
 * 1. Use Floyd’s Cycle Detection Algorithm (Tortoise & Hare).
 * 2. Move slow by 1 step and fast by 2 steps.
 * 3. If they meet → cycle exists.
 * 4. Reset slow to head.
 * 5. Move both one step at a time → meeting point is cycle start.
 *
 * Why it works:
 * Distance from head to cycle start = distance from meeting point to cycle start.
 *
 * ⏱ Time Complexity: O(n)
 * 💾 Space Complexity: O(1)
 *
 * Alternative Approaches:
 * 1. Use HashSet → store visited nodes (O(n) space)
 * 2. Modify node structure (not recommended in interviews)
 */

class Solution {
public:
    int cycleStart(Node* head) {

        // Step 1: Initialize pointers
        Node* slow = head;
        Node* fast = head;

        // Step 2: Detect cycle
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            // Cycle detected
            if (slow == fast) {

                // Step 3: Find cycle start
                slow = head;

                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }

                return slow->data; // cycle starting node
            }
        }

        // No cycle
        return -1;
    }
};
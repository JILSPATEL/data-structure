/**
 * 🔁 Reverse a Linked List
 * -----------------------------------
 * Given the head of a singly linked list, reverse the list and return new head.
 *
 * ✅ Approaches:
 *
 * 1. Iterative (3-pointer method)
 *    - Use prev, curr, next pointers
 *    - Reverse links step by step
 *
 * 2. Recursive
 *    - Reverse rest of list first
 *    - Fix current node at the end
 *
 * -----------------------------------
 * Time Complexity:
 *   - Iterative: O(n)
 *   - Recursive: O(n)
 *
 * Space Complexity:
 *   - Iterative: O(1)
 *   - Recursive: O(n) (due to recursion stack)
 */

class Solution {
public:

    // 🔹 Iterative Approach
    Node* reverseList(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;
        Node* nextNode = nullptr;

        while (curr) {
            nextNode = curr->next;  // store next
            curr->next = prev;      // reverse link
            prev = curr;            // move prev
            curr = nextNode;        // move curr
        }
        return prev;
    }

    // 🔹 Recursive Approach
    Node* reverseListRecursive(Node* head) {
        // Base case: empty or single node
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Reverse rest of the list
        Node* newHead = reverseListRecursive(head->next);

        // Fix current node
        head->next->next = head;  // reverse link
        head->next = nullptr;     // break old link

        return newHead;
    }
};
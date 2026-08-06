/**
 * Merge Two Sorted Linked Lists (Iterative Approach)
 *
 * Problem:
 * Given two sorted linked lists, merge them into a single sorted linked list.
 *
 * Example:
 * Input:
 *   List1: 1 → 3 → 5
 *   List2: 2 → 4 → 6
 *
 * Output:
 *   1 → 2 → 3 → 4 → 5 → 6
 *
 * ------------------------------------------------------------
 * APPROACHES:
 *
 * 1) Brute Force:
 *    - Copy all elements into array, sort, rebuild list
 *    - Time: O((n+m) log(n+m)), Space: O(n+m)
 *
 * 2) Recursive:
 *    - Compare nodes and recurse
 *    - Elegant but uses stack space
 *
 * 3) Iterative (Used Here - Optimal):
 *    - Use two pointers and build merged list
 *    - Time: O(n + m), Space: O(1)
 *
 * ------------------------------------------------------------
 */

class Solution {
public:
    Node* sortedMerge(Node* head1, Node* head2) {

        // Edge cases
        if (!head1) return head2;
        if (!head2) return head1;

        Node* head = nullptr;
        Node* tail = nullptr;

        // Step 1: Initialize head and tail
        if (head1->data <= head2->data) {
            head = tail = head1;
            head1 = head1->next;
        } else {
            head = tail = head2;
            head2 = head2->next;
        }

        // Step 2: Merge both lists
        while (head1 && head2) {
            if (head1->data <= head2->data) {
                tail->next = head1;
                tail = head1;
                head1 = head1->next;
            } else {
                tail->next = head2;
                tail = head2;
                head2 = head2->next;
            }
        }

        // Step 3: Attach remaining nodes
        if (head1) {
            tail->next = head1;
        } else {
            tail->next = head2;
        }

        return head;
    }
};
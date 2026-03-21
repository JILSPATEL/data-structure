/**
 * Find all pairs in a sorted doubly linked list whose sum equals target.
 *
 * Approach:
 * 1. Use TWO POINTER technique:
 *    - 'start' → points to beginning of list
 *    - 'end'   → points to last node of list
 *
 * 2. Move pointers based on sum:
 *    - If (start + end == target) → store pair, move both pointers
 *    - If (sum > target) → decrease sum → move 'end' backward
 *    - If (sum < target) → increase sum → move 'start' forward
 *
 * 3. Stop when:
 *    - start meets end OR crosses it
 *
 * Why this works?
 * - Since the DLL is SORTED, we can efficiently adjust pointers
 *   instead of checking all pairs (which would be O(n^2)).
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) (excluding result storage)
 *
 * Edge Cases:
 * - Empty list
 * - Single node
 * - No valid pairs
 */

class Solution {
public:
    vector<pair<int, int>> findPairsWithGivenSum(Node *head, int target) {
        
        // Edge case: empty list or only one node
        if (!head || !head->next) {
            return {};
        }

        vector<pair<int, int>> res;

        // Pointer to beginning
        Node* start = head;

        // Pointer to end (last node)
        Node* end = head;
        while (end->next != NULL) {
            end = end->next;
        }

        // Two pointer traversal
        while (start != NULL && end != NULL && start != end && end->next != start) {
            
            int sum = start->data + end->data;

            if (sum == target) {
                // Found valid pair
                res.push_back({start->data, end->data});

                // Move both pointers
                start = start->next;
                end = end->prev;
            }
            else if (sum > target) {
                // Need smaller sum → move end backward
                end = end->prev;
            }
            else {
                // Need larger sum → move start forward
                start = start->next;
            }
        }

        return res;
    }
};
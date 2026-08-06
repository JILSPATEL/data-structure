/**
 * Merge K Sorted Linked Lists (Divide & Conquer Approach)
 *
 * Problem:
 * Given K sorted linked lists, merge them into one sorted linked list.
 *
 * Example:
 * Input:
 *   List1: 1 → 4 → 7
 *   List2: 2 → 5 → 8
 *   List3: 3 → 6 → 9
 *
 * Output:
 *   1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9
 *
 * ------------------------------------------------------------
 * APPROACHES:
 *
 * 1) Brute Force:
 *    - Put all elements in array, sort, rebuild list
 *    - Time: O(N log N), Space: O(N)
 *
 * 2) Min Heap:
 *    - Push heads into priority queue
 *    - Time: O(N log K), Space: O(K)
 *
 * 3) Divide & Conquer (Used Here - Optimal):
 *    - Merge lists in pairs (like merge sort)
 *    - Time: O(N log K), Space: O(1) extra (ignoring recursion)
 *
 * ------------------------------------------------------------
 */

class Solution {
public:

    // Merge two sorted lists (same as your previous solution)
    Node* merge(Node* head1, Node* head2) {
        if (!head1) return head2;
        if (!head2) return head1;

        Node* head = nullptr;
        Node* tail = nullptr;

        // Initialize head
        if (head1->data <= head2->data) {
            head = tail = head1;
            head1 = head1->next;
        } else {
            head = tail = head2;
            head2 = head2->next;
        }

        // Merge process
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

        // Attach remaining
        if (head1) tail->next = head1;
        else tail->next = head2;

        return head;
    }

    // Merge K lists
    Node* mergeKLists(vector<Node*>& arr) {
        if (arr.empty()) return nullptr;

        // Keep merging until only one list remains
        while (arr.size() > 1) {

            vector<Node*> temp;

            // Merge pairs
            for (int i = 0; i < arr.size(); i += 2) {
                Node* head1 = arr[i];
                Node* head2 = (i + 1 < arr.size()) ? arr[i + 1] : nullptr;

                temp.push_back(merge(head1, head2));
            }

            // Move to next level
            arr = temp;
        }

        return arr[0];
    }
};
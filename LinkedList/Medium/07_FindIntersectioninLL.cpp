/**
 * Problem: Intersection Point of Two Linked Lists
 *
 * Description:
 * Given two singly linked lists, return the node at which they intersect.
 * If the two linked lists have no intersection, return NULL.
 *
 * Approaches:
 *
 * 1) Brute Force:
 *    - For each node in list1, traverse list2
 *    - Time: O(N * M)
 *
 * 2) Better Approach (Used Here - Length Difference):
 *    - Find lengths of both lists
 *    - Move pointer of longer list ahead by difference
 *    - Traverse both lists together to find intersection
 *    - Time: O(N + M), Space: O(1)
 *
 * 3) Optimal (Two Pointer Trick):
 *    - Move both pointers, switch heads when reaching end
 *    - They meet at intersection
 *    - Time: O(N + M), Space: O(1)
 */

class Solution {
public:
    Node* intersectPoint(Node* head1, Node* head2) {
        int len1 = 0, len2 = 0;

        Node* temp1 = head1;
        Node* temp2 = head2;

        // Calculate lengths
        while (temp1) {
            len1++;
            temp1 = temp1->next;
        }
        while (temp2) {
            len2++;
            temp2 = temp2->next;
        }

        temp1 = head1;
        temp2 = head2;

        int diff = abs(len1 - len2);

        // Align both pointers
        if (len1 > len2) {
            while (diff--) temp1 = temp1->next;
        } else {
            while (diff--) temp2 = temp2->next;
        }

        // Find intersection (IMPORTANT: compare nodes, not values)
        while (temp1 && temp2) {
            if (temp1 == temp2) {
                return temp1;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        return nullptr;
    }
};

//Optimized

Node* intersectPoint(Node* head1, Node* head2) {
    Node* a = head1;
    Node* b = head2;

    while (a != b) {
        a = (a == nullptr) ? head2 : a->next;
        b = (b == nullptr) ? head1 : b->next;
    }

    return a; // intersection or nullptr
}
#include <iostream>
using namespace std;
/**
 * Problem: Sort a Linked List (Merge Sort on Linked List)
 *
 * Description:
 * Given the head of a linked list, return the list after sorting it in ascending order.
 *
 * Approaches:
 *
 * 1) Brute Force:
 *    - Copy values into an array/vector
 *    - Sort the array
 *    - Rebuild the linked list
 *    - Time: O(N log N), Space: O(N)
 *
 * 2) Optimal (Used Here - Merge Sort on Linked List):
 *    - Divide list into two halves using slow-fast pointer
 *    - Recursively sort both halves
 *    - Merge two sorted lists
 *    - Time: O(N log N), Space: O(log N) (recursion stack)
 *
 * Key Functions:
 *    - findMid(): Finds middle of linked list
 *    - merge(): Merges two sorted linked lists
 *    - sortList(): Main recursive merge sort function
 */

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:

    // Function to find middle of linked list
    ListNode* findMid(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next; // ensures left half is smaller

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // Function to merge two sorted linked lists
    ListNode* merge(ListNode* list1, ListNode* list2) {
        if (!list1) return list2;
        if (!list2) return list1;

        ListNode* head = nullptr;

        // Initialize head
        if (list1->val <= list2->val) {
            head = list1;
            list1 = list1->next;
        } else {
            head = list2;
            list2 = list2->next;
        }

        ListNode* tail = head;

        // Merge process
        while (list1 && list2) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        // Attach remaining nodes
        if (list1) tail->next = list1;
        if (list2) tail->next = list2;

        return head;
    }

    // Main function to sort linked list
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        // Divide
        ListNode* mid = findMid(head);
        ListNode* right = mid->next;
        mid->next = nullptr;
        ListNode* left = head;

        // Conquer
        left = sortList(left);
        right = sortList(right);

        // Combine
        return merge(left, right);
    }
};

// Helper to append nodes
ListNode* appendNode(ListNode* head, int val) {
    ListNode* newNode = new ListNode(val);
    if (!head) return newNode;
    ListNode* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

// Helper to print list
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    ListNode* head = nullptr;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        head = appendNode(head, val);
    }

    Solution s;
    head = s.sortList(head);

    cout << "Sorted list: ";
    printList(head);

    return 0;
}

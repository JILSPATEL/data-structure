#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x){
        val=x;
        next=nullptr;
    }
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* fast = dummy;
        ListNode* slow = dummy;

        for (int i = 0; i <= n; i++) {
            if (fast) fast = fast->next;
        }

        while (fast) {
            slow = slow->next;
            fast = fast->next;
        }

        ListNode* toDelete = slow->next;
        if (toDelete)
            slow->next = toDelete->next;

        delete toDelete;
        ListNode* newHead = dummy->next;
        delete dummy;
        return newHead;
    }
};

// Utility function to print the list
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    cout << "Enter elements to add to the linked list (-1 to stop):\n";
    int val;
    while (cin >> val && val != -1) {
        ListNode* newNode = new ListNode(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    int n;
    cout << "Enter the value of n (to remove nth node from end): ";
    cin >> n;

    Solution sol;
    head = sol.removeNthFromEnd(head, n);

    cout << "Linked list after removal:\n";
    printList(head);

    return 0;
}

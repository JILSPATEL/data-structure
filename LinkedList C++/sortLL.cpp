#include <iostream>
using namespace std;

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
    ListNode* merge(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* temp = dummy;

        while (list1 && list2) {
            if (list1->val <= list2->val) {
                temp->next = list1;
                list1 = list1->next;
            } else {
                temp->next = list2;
                list2 = list2->next;
            }
            temp = temp->next;
        }
        while (list1) {
            temp->next = list1;
            list1 = list1->next;
            temp = temp->next;
        }
        while (list2) {
            temp->next = list2;
            list2 = list2->next;
            temp = temp->next;
        }

        return dummy->next;
    }

    ListNode* findMid(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* fast = head->next;
        ListNode* slow = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* mid = findMid(head);
        ListNode* right = mid->next;
        mid->next = nullptr;
        ListNode* left = head;

        left = sortList(left);
        right = sortList(right);

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

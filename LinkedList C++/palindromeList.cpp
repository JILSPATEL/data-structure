#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) {
        val = x;
        next = nullptr;
    }
};

class Solution {
public:
    ListNode* reverse(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        return prev;
    }

    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;

        ListNode* slow = head;
        ListNode* fast = head;

        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* secondHalf = reverse(slow->next);
        ListNode* firstHalf = head;
        ListNode* temp = secondHalf;

        while (temp) {
            if (firstHalf->val != temp->val) {
                reverse(secondHalf); // restore original list
                return false;
            }
            firstHalf = firstHalf->next;
            temp = temp->next;
        }

        reverse(secondHalf); // restore original list
        return true;
    }
};

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

    Solution sol;
    if (sol.isPalindrome(head)) {
        cout << "The linked list is a palindrome.\n";
    } else {
        cout << "The linked list is not a palindrome.\n";
    }

    return 0;
}

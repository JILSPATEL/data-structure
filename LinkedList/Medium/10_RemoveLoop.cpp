#include <iostream>
using namespace std;

class ListNode
{
public:
    int data;
    ListNode *next;
    ListNode(int x)
    {
        data = x;
        next = nullptr;
    }
};

void loopLength(ListNode *slow, ListNode *fast)
{
    int cnt = 1;
    fast = fast->next;
    while (slow != fast)
    {
        cnt++;
        fast = fast->next;
    }
    cout << "\nLoop Length: " << cnt << endl;
}

void removeLoop(ListNode *head)
{
    if(!head || !head->next) return;
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            loopLength(slow, fast);
            slow = head;

            if (slow == fast)
            {
                while (fast->next != slow)
                {
                    fast = fast->next;
                }
            }
            else
            {
                while (slow->next != fast->next)
                {
                    slow = slow->next;
                    fast = fast->next;
                }
            }
            fast->next = nullptr;
            return;
        }
    }
}

void printList(ListNode *head)
{
    ListNode *temp = head;
    while (temp)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main()
{
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    int n, val, m;
    cout << "How many elements do you want to insert: ";
    cin >> n;
    cout << "\nEnter " << n << " elements\n";

    while (n > 0)
    {
        cin >> val;
        ListNode *newNode = new ListNode(val);
        if (!head)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        n--;
    }

    cout << "\nOn which node (0-based index) should the last node point? Enter -1 for no loop.\n";
    cin >> m;
    if (m >= 0)
    {
        ListNode *temp = head;
        while (m > 0 && temp)
        {
            temp = temp->next;
            m--;
        }
        if (temp)
        {
            tail->next = temp;
        }
    }
    removeLoop(head);
    printList(head);
    return 0;
}

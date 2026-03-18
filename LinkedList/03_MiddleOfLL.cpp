/**
 * Problem: Find Middle Element of Linked List
 *
 * Description:
 * Given the head of a singly linked list, return the value of the middle node.
 * If there are two middle nodes (even length), return the second middle.
 *
 * Intuition:
 * Count total nodes, then move to the middle index.
 *
 * Approach (Two Pass - Your Approach):
 * 1. Traverse the list to count total nodes (cnt)
 * 2. Compute middle index → mid = cnt / 2
 * 3. Traverse again to reach the mid-th node
 * 4. Return its value
 *
 * Alternative Approaches:
 *
 * 1. Optimal (Fast & Slow Pointer - Single Pass):
 *    - Use two pointers:
 *        slow moves 1 step
 *        fast moves 2 steps
 *    - When fast reaches end, slow is at middle
 *
 * 2. Your Approach (Two Pass - Used here):
 *    - Simple and intuitive
 *    - Slightly less efficient due to two traversals
 *
 * Time Complexity:
 * - O(n) + O(n/2) ≈ O(n)
 *
 * Space Complexity:
 * - O(1)
 */
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Node class represents a node in a linked list
class Node
{
public:
    int data;
    Node *next;

    Node(int data1)
    {
        data = data1;
        next = nullptr;
    }
};

Node *findMiddle(Node *head)
{

    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

int main()
{
    Node *head = nullptr;
    Node *tail = nullptr;

    cout << "Enter elements to add to the linked list (-1 to stop):\n";
    int val;
    while (cin >> val && val != -1)
    {
        Node *newNode = new Node(val);
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
    }

    Node *middleNode = findMiddle(head);
    cout << "The middle node value is: " << middleNode->data << endl;

    return 0;
}
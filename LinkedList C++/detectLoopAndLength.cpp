#include <iostream>
using namespace std;

// Node class represents a node in a linked list
class Node {
public:
    int data;
    Node* next;
    Node(int data1) {
        data = data1;
        next = nullptr;
    }
};

// Function to return the length of loop when slow and fast are on the same node
int findLength(Node* slow, Node* fast) {
    int cnt = 1;
    fast = fast->next;
    while (slow != fast) {
        cnt++;
        fast = fast->next;
    }
    return cnt;
}

// Function to find the length of the loop in a linked list
int lengthOfLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return findLength(slow, fast);
        }
    }

    return 0;
}

int main() {
    Node *head = nullptr;
    Node *tail = nullptr;
    cout << "Enter numbers to add to the linked list (-1 to stop):\n";
    int val;
    while (cin >> val && val != -1) {
        Node *newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // ✅ Create a loop manually for testing: connect tail to 2nd node
    if (head && head->next) {
        tail->next = head->next;  // Creates a loop for testing
    }

    int loopLength = lengthOfLoop(head);
    if (loopLength > 0) {
        cout << "Length of the loop: " << loopLength << endl;
    } else {
        cout << "No loop found in the linked list." << endl;
    }

    return 0;
}


#include <stdio.h>

#define MAX 5

int arr[MAX];
int top = -1;

// PUSH: Insert element into stack
void push(int x) {
    if (top == MAX - 1) {
        printf("Stack Overflow! Cannot insert element.\n");
        return;
    }

    top++;
    arr[top] = x;

    printf("%d inserted successfully.\n", x);
}

// POP: Remove top element
void pop() {
    if (top == -1) {
        printf("Stack Underflow! Stack is empty.\n");
        return;
    }

    printf("Deleted element: %d\n", arr[top]);
    top--;
}

// PEEK: Get top element
void peek() {
    if (top == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Top element: %d\n", arr[top]);
}

// DISPLAY: Print all stack elements
void display() {
    if (top == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("\nStack elements (TOP to BOTTOM):\n");

    for (int i = top; i >= 0; i--) {
        printf("%d\n", arr[i]);
    }
}

// Check whether stack is empty
int isEmpty() {
    return top == -1;
}

// Check whether stack is full
int isFull() {
    return top == MAX - 1;
}

int main() {
    int choice, value;

    while (1) {
        printf("\n----- STACK MENU -----\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("5. CHECK EMPTY\n");
        printf("6. CHECK FULL\n");
        printf("7. EXIT\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter element: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
                break;

            case 3:
                peek();
                break;

            case 4:
                display();
                break;

            case 5:
                if (isEmpty())
                    printf("Stack is Empty.\n");
                else
                    printf("Stack is Not Empty.\n");
                break;

            case 6:
                if (isFull())
                    printf("Stack is Full.\n");
                else
                    printf("Stack is Not Full.\n");
                break;

            case 7:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
/*
Operation	Time Complexity
Push	    O(1)
Pop	        O(1)
Peek	    O(1)
Display	    O(n)
isEmpty	    O(1)
isFull	    O(1)
*/
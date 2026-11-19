#include <stdio.h>
#include <stdlib.h>

#define MAX 5
int arr[MAX];
int front = -1;
int rear=-1;

void enqueue(int x){
    if(rear==MAX-1){
        printf("Queue Overflow! Cannot insert element.\n");
        return;
    }
    if(front==-1){
        front=0;
    }
    rear++;
    arr[rear]=x;
    printf("%d inserted successfully.\n",x);
}

void dequeue(){
    if(front==-1 || front>rear){
        printf("Queue Underflow.\n");
        return;
    }
    printf("Deleted element: %d\n",arr[front]);
    if(front==rear){
        front=-1;
        rear=-1;
    }else{
        front++;
    }
}

void peek(){
    if(front==-1){
        printf("Queue is Empty. \n");
        return;
    }
    printf("Front Element: %d\n",arr[front]);
}

void display(){
    if(front==-1){
        printf("Queue id empty.\n");
        return;
    }
    printf("\nQueue elements (front to rear):\n");
    for(int i=front;i<=rear;i++){
        printf("%d",arr[i]);
    }
    printf("\n");
}

int isEmpty() {
    return front == -1;
}

int isFull() {
    return rear == MAX - 1;
}

int main() {

    int choice, value;

    while (1) {

        printf("\n----- QUEUE MENU -----\n");
        printf("1. ENQUEUE\n");
        printf("2. DEQUEUE\n");
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
                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                peek();
                break;

            case 4:
                display();
                break;

            case 5:
                if (isEmpty())
                    printf("Queue is Empty.\n");
                else
                    printf("Queue is Not Empty.\n");
                break;

            case 6:
                if (isFull())
                    printf("Queue is Full.\n");
                else
                    printf("Queue is Not Full.\n");
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
ENQUEUE	        O(1)
DEQUEUE	        O(1)
PEEK	        O(1)
DISPLAY	        O(n)
isEmpty	        O(1)
isFull	        O(1)
*/
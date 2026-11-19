/*
Definition: This program demonstrates the concept of "Call by Reference" in C. In this method, the addresses of the arguments are passed to the function, and any changes made to the parameters inside the function affect the original arguments.
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
    printf("Inside function: x = %d, y = %d\n", *x, *y);
}

int main()
{
    int a = 10;
    int b = 20;

    printf("Before function call: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("After function call: a = %d, b = %d\n", a, b);

    return 0;
}

/*
Output:
Before function call: a = 10, b = 20
Inside function: x = 20, y = 10
After function call: a = 10, b = 20
*/
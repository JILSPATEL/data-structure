#include <stdio.h>

// typedef gives a shorter name, Student, to this structure type.
// Without typedef, we would write: struct Student student1;
typedef struct {
    // Stores the student's name as a character array.
    char name[50];
    // Stores the student's age.
    int age;
    // Stores the student's grade point average.
    float gpa;
} Student;

int main() {
    // Create and initialize a Student variable using the typedef name.
    Student student1 = {"John Doe", 20, 3.5f};

    // Access structure members using the dot (.) operator.
    printf("Name: %s\n", student1.name);
    printf("Age: %d\n", student1.age);
    printf("GPA: %.2f\n", student1.gpa);

    return 0;
}
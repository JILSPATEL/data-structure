struct Student {
    char name[50];
    int age;
    float gpa;
};

int main() {
    struct Student student1;

    snprintf(student1.name, sizeof(student1.name), "John Doe");
    student1.age = 20;
    student1.gpa = 3.5;

    // Print the values of the structure fields
    printf("Student Name: %s\n", student1.name);
    printf("Student Age: %d\n", student1.age);
    printf("Student GPA: %.2f\n", student1.gpa);

    return 0;
}

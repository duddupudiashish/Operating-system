#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

void addEmployee(FILE *fp) {
    struct Employee emp;
    printf("Enter ID: ");
    scanf("%d", &emp.id);
    printf("Enter Name: ");
    scanf("%s", emp.name);
    printf("Enter Salary: ");
    scanf("%f", &emp.salary);

    fseek(fp, 0, SEEK_END);  
    fwrite(&emp, sizeof(emp), 1, fp);
    printf("Employee record added.\n");
}

void displayEmployees(FILE *fp) {
    struct Employee emp;
    rewind(fp);  

    printf("\nEmployee List:\n");
    while (fread(&emp, sizeof(emp), 1, fp)) {
        printf("ID: %d\tName: %s\tSalary: %.2f\n", emp.id, emp.name, emp.salary);
    }
}

void searchByID(FILE *fp, int id) {
    struct Employee emp;
    rewind(fp);
    int found = 0;

    while (fread(&emp, sizeof(emp), 1, fp)) {
        if (emp.id == id) {
            printf("\nEmployee Found:\n");
            printf("ID: %d\tName: %s\tSalary: %.2f\n", emp.id, emp.name, emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
}

int main() {
    FILE *fp;
    int choice, id;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("employee.dat", "wb+");  
        if (fp == NULL) {
            printf("Error opening file.\n");
            return 1;
        }
    }

    do {
        printf("\n--- Employee Management ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search by ID\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(fp);
                break;
            case 2:
                displayEmployees(fp);
                break;
            case 3:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                searchByID(fp, id);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option.\n");
        }

    } while (choice != 4);

    fclose(fp);
    return 0;
}


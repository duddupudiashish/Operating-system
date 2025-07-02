#include <stdio.h>
#include <string.h>

#define MAX 100

struct Directory {
    char files[MAX][20];
    int fileCount;
};

void createFile(struct Directory *dir, char filename[]) {
    for (int i = 0; i < dir->fileCount; i++) {
        if (strcmp(dir->files[i], filename) == 0) {
            printf("File '%s' already exists!\n", filename);
            return;
        }
    }

    strcpy(dir->files[dir->fileCount], filename);
    dir->fileCount++;
    printf("File '%s' created successfully.\n", filename);
}

void deleteFile(struct Directory *dir, char filename[]) {
    int found = 0;
    for (int i = 0; i < dir->fileCount; i++) {
        if (strcmp(dir->files[i], filename) == 0) {
            found = 1;
            for (int j = i; j < dir->fileCount - 1; j++) {
                strcpy(dir->files[j], dir->files[j + 1]);
            }
            dir->fileCount--;
            printf("File '%s' deleted successfully.\n", filename);
            break;
        }
    }
    if (!found) {
        printf("File '%s' not found.\n", filename);
    }
}

void searchFile(struct Directory *dir, char filename[]) {
    for (int i = 0; i < dir->fileCount; i++) {
        if (strcmp(dir->files[i], filename) == 0) {
            printf("File '%s' found at position %d.\n", filename, i + 1);
            return;
        }
    }
    printf("File '%s' not found.\n", filename);
}

void displayFiles(struct Directory *dir) {
    if (dir->fileCount == 0) {
        printf("Directory is empty.\n");
    } else {
        printf("Files in directory:\n");
        for (int i = 0; i < dir->fileCount; i++) {
            printf("%d. %s\n", i + 1, dir->files[i]);
        }
    }
}

int main() {
    struct Directory dir;
    dir.fileCount = 0;

    int choice;
    char filename[20];

    printf("Single-Level Directory Simulation\n");

    do {
        printf("\nMenu:\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter filename to create: ");
                scanf("%s", filename);
                createFile(&dir, filename);
                break;
            case 2:
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                deleteFile(&dir, filename);
                break;
            case 3:
                printf("Enter filename to search: ");
                scanf("%s", filename);
                searchFile(&dir, filename);
                break;
            case 4:
                displayFiles(&dir);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}


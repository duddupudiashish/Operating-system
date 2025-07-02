#include <stdio.h>
#include <string.h>

struct Directory {
    char dname[10], fname[10][10];
    int fcount;
} dir[10];

int main() {
    int i, j, userCount = 0, choice;
    char name[10], fname[10];

    do {
        printf("\n1. Create User\n2. Create File\n3. List Files\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter user name: ");
                scanf("%s", dir[userCount].dname);
                dir[userCount].fcount = 0;
                userCount++;
                break;

            case 2:
                printf("Enter user name: ");
                scanf("%s", name);
                for (i = 0; i < userCount; i++) {
                    if (strcmp(name, dir[i].dname) == 0) {
                        printf("Enter file name: ");
                        scanf("%s", dir[i].fname[dir[i].fcount]);
                        dir[i].fcount++;
                        printf("File added.\n");
                        break;
                    }
                }
                if (i == userCount) printf("User not found.\n");
                break;

            case 3:
                for (i = 0; i < userCount; i++) {
                    printf("User: %s\n", dir[i].dname);
                    for (j = 0; j < dir[i].fcount; j++)
                        printf("  File: %s\n", dir[i].fname[j]);
                }
                break;
        }
    } while (choice != 4);

    return 0;
}


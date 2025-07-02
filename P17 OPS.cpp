#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int processes, resources;
    int Allocation[MAX_PROCESSES][MAX_RESOURCES];
    int Max[MAX_PROCESSES][MAX_RESOURCES];
    int Need[MAX_PROCESSES][MAX_RESOURCES];
    int Available[MAX_RESOURCES];
    int Finish[MAX_PROCESSES] = {0}, SafeSequence[MAX_PROCESSES];
    
    printf("Enter number of processes: ");
    scanf("%d", &processes);

    printf("Enter number of resources: ");
    scanf("%d", &resources);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            scanf("%d", &Allocation[i][j]);

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            scanf("%d", &Max[i][j]);

    printf("Enter Available Resources:\n");
    for (int i = 0; i < resources; i++)
        scanf("%d", &Available[i]);

    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    
    int count = 0;
    while (count < processes) {
        bool found = false;
        for (int p = 0; p < processes; p++) {
            if (!Finish[p]) {
                int j;
                for (j = 0; j < resources; j++)
                    if (Need[p][j] > Available[j])
                        break;

                if (j == resources) {  
                    for (int k = 0; k < resources; k++)
                        Available[k] += Allocation[p][k];
                    SafeSequence[count++] = p;
                    Finish[p] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("\nSystem is NOT in a safe state (deadlock may occur).\n");
            return 1;
        }
    }

    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < processes; i++)
        printf("P%d ", SafeSequence[i]);
    printf("\n");

    return 0;
}


#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
};

int main() {
    int n, time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input details
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].isCompleted = 0;
    }

    while (completed != n) {
        int idx = -1;
        int minBT = 9999;

        // Find the shortest job among arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= time && !p[i].isCompleted && p[i].burstTime < minBT) {
                minBT = p[i].burstTime;
                idx = i;
            }
        }

        if (idx != -1) {
            // Execute the selected process
            time += p[idx].burstTime;
            p[idx].completionTime = time;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            p[idx].isCompleted = 1;
            completed++;

            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;
        } else {
            // If no process has arrived yet, move time forward
            time++;
        }
    }

    // Print the results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid,
               p[i].arrivalTime, p[i].burstTime, p[i].completionTime,
               p[i].turnaroundTime, p[i].waitingTime);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}


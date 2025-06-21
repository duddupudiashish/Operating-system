#include <stdio.h>

struct Process {
    int pid;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
};

// Swap function for sorting
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n, totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input burst time and priority for each process
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time and Priority for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].burstTime, &p[i].priority);
    }

    // Sort by priority (lower number = higher priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }

    // Calculate waiting and turnaround time
    p[0].waitingTime = 0;
    for (int i = 1; i < n; i++) {
        p[i].waitingTime = p[i - 1].waitingTime + p[i - 1].burstTime;
    }

    for (int i = 0; i < n; i++) {
        p[i].turnaroundTime = p[i].waitingTime + p[i].burstTime;
        totalWaitingTime += p[i].waitingTime;
        totalTurnaroundTime += p[i].turnaroundTime;
    }

    // Output
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].burstTime, p[i].priority, p[i].waitingTime, p[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    return 0;
}


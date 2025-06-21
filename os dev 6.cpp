#include <stdio.h>

#define MAX 100

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
};

int main() {
    int n, time = 0, completed = 0, minPriority;
    int shortest = -1;

    struct Process p[MAX];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input processes
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time and Priority for Process %d: ", p[i].pid);
        scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
        p[i].remainingTime = p[i].burstTime;
        p[i].isCompleted = 0;
    }

    while (completed != n) {
        shortest = -1;
        minPriority = 9999;

        // Find the process with highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= time && !p[i].isCompleted && p[i].priority < minPriority && p[i].remainingTime > 0) {
                minPriority = p[i].priority;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++; // No process ready to execute
            continue;
        }

        // Run the process for 1 unit time
        p[shortest].remainingTime--;
        time++;

        // If process completes
        if (p[shortest].remainingTime == 0) {
            p[shortest].isCompleted = 1;
            completed++;
            p[shortest].completionTime = time;
            p[shortest].turnaroundTime = p[shortest].completionTime - p[shortest].arrivalTime;
            p[shortest].waitingTime = p[shortest].turnaroundTime - p[shortest].burstTime;
        }
    }

    // Output results
    float avgWT = 0, avgTAT = 0;
    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].priority,
               p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
        avgWT += p[i].waitingTime;
        avgTAT += p[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f", avgWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT / n);

    return 0;
}


#include <stdio.h>

int main() {
    int i, n, time, remain, time_quantum;
    int wait_time = 0, turnaround_time = 0;
    int bt[10], rt[10]; // bt = burst time, rt = remaining time

    printf("Enter the total number of processes (max 10): ");
    scanf("%d", &n);

    remain = n;

    printf("Enter the burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Copy burst time to remaining time
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    printf("\nProcess\t| Turnaround Time | Waiting Time\n");
    printf("---------------------------------------\n");

    int t = 0; // Current time
    int done;

    while (remain != 0) {
        done = 1;
        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0;

                if (rt[i] > time_quantum) {
                    t += time_quantum;
                    rt[i] -= time_quantum;
                } else {
                    t += rt[i];
                    wait_time += t - bt[i];
                    turnaround_time += t;
                    printf("P[%d]\t|\t%d\t|\t%d\n", i + 1, t, t - bt[i]);
                    rt[i] = 0;
                    remain--;
                }
            }
        }

        if (done == 1)
            break;
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)wait_time / n);
    printf("Average Turnaround Time = %.2f\n", (float)turnaround_time / n);

    return 0;
}


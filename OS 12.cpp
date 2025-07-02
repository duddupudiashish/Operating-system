#include <windows.h>
#include <stdio.h>

#define PHILOSOPHERS 5

HANDLE forks[PHILOSOPHERS];

DWORD WINAPI philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % PHILOSOPHERS;

    while (1) {
       
        printf("Philosopher %d thinking\n", id);
        Sleep(1000);

        
        if (left < right) {
            WaitForSingleObject(forks[left], INFINITE);
            WaitForSingleObject(forks[right], INFINITE);
        } else {
            WaitForSingleObject(forks[right], INFINITE);
            WaitForSingleObject(forks[left], INFINITE);
        }

        
        printf("Philosopher %d EATING\n", id);
        Sleep(1000);

     
        ReleaseMutex(forks[left]);
        ReleaseMutex(forks[right]);
    }
    return 0;
}

int main() {
    int ids[PHILOSOPHERS];
    HANDLE phils[PHILOSOPHERS];

   
    for (int i = 0; i < PHILOSOPHERS; i++) {
        forks[i] = CreateMutex(NULL, FALSE, NULL);
    }

    for (int i = 0; i < PHILOSOPHERS; i++) {
        ids[i] = i;
        phils[i] = CreateThread(NULL, 0, philosopher, &ids[i], 0, NULL);
    }

   
    Sleep(20000);

   
    for (int i = 0; i < PHILOSOPHERS; i++) {
        CloseHandle(phils[i]);
        CloseHandle(forks[i]);
    }
    return 0;
}

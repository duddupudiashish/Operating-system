#include <windows.h>
#include <stdio.h>

#define NUM_THREADS 3

// Thread function prototype
DWORD WINAPI ThreadFunction(LPVOID lpParam);

int main() {
    HANDLE threads[NUM_THREADS];
    DWORD threadIds[NUM_THREADS];
    int threadArgs[NUM_THREADS];
    
    printf("Main thread started (ID: %lu)\n", GetCurrentThreadId());
    
    // Create multiple threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadArgs[i] = i + 1;
        threads[i] = CreateThread(
            NULL,                   // Default security attributes
            0,                      // Default stack size
            ThreadFunction,         // Thread function
            &threadArgs[i],         // Argument to thread function
            0,                      // Default creation flags
            &threadIds[i]           // Returns the thread identifier
        );
        
        if (threads[i] == NULL) {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }
    
    // Wait for all threads to complete
    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);
    
    // Close thread handles
    for (int i = 0; i < NUM_THREADS; i++) {
        CloseHandle(threads[i]);
    }
    
    printf("All threads completed. Main thread exiting.\n");
    return 0;
}

// Function that each thread will execute
DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    int threadNum = *(int*)lpParam;
    
    printf("Thread %d started (ID: %lu)\n", threadNum, GetCurrentThreadId());
    
    // Simulate some work
    for (int i = 1; i <= 3; i++) {
        printf("Thread %d: working... (%d/3)\n", threadNum, i);
        Sleep(1000); // Sleep for 1 second
    }
    
    printf("Thread %d completed\n", threadNum);
    return 0;
}

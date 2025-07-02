#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readcount = 0;
sem_t wrt;             
pthread_mutex_t mutex; 

void* writer(void* arg) {
    int id = *(int*)arg;
    sem_wait(&wrt);  

    printf("Writer %d is writing...\n", id);
    sleep(1);  
    printf("Writer %d has finished writing.\n", id);

    sem_post(&wrt);  
    return NULL;
}

void* reader(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);  
    pthread_mutex_unlock(&mutex);

    printf("Reader %d is reading...\n", id);
    sleep(1);  
    printf("Reader %d has finished reading.\n", id);

    pthread_mutex_lock(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);  
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    int ids[5] = {1, 2, 3, 4, 5};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    
    for (int i = 0; i < 5; i++)
        pthread_create(&r[i], NULL, reader, &ids[i]);

    
    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &ids[i]);

    
    for (int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}


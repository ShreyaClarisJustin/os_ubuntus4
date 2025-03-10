//chatgpt
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, wrt;
int read_count = 0;

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&wrt);
        sem_post(&mutex);

        // Reading the resource

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&wrt);
        sem_post(&mutex);

        // Reading complete
    }
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&wrt);

        // Writing to the resource

        sem_post(&wrt);

        // Writing complete
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < NUM_READERS; i++)
        pthread_create(&readers[i], NULL, reader, NULL);

    for (int i = 0; i < NUM_WRITERS; i++)
        pthread_create(&writers[i], NULL, writer, NULL);

    for (int i = 0; i < NUM_READERS; i++)
        pthread_join(readers[i], NULL);

    for (int i = 0; i < NUM_WRITERS; i++)
        pthread_join(writers[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

typedef struct {
    int value;
} Semaphore;

void wait(Semaphore *s) {
    while (s->value <= 0);  // Busy wait
    s->value--;
}

void signal(Semaphore *s) {
    s->value++;
}

int buffer[BUFFER_SIZE];
int count = 0;

Semaphore empty, full;

void *producer(void *arg) {
    for (int i = 1; i <= 10; i++) {
        wait(&empty);
        buffer[count++] = i;
        printf("Produced: %d\n", i);
        signal(&full);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= 10; i++) {
        wait(&full);
        int item = buffer[--count];
        printf("Consumed: %d\n", item);
        signal(&empty);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    empty.value = BUFFER_SIZE;
    full.value = 0;

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}

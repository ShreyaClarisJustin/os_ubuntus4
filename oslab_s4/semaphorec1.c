#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 6

typedef struct {
    int buffer[BUFFER_SIZE];
    int in, out;
    int empty, full, mutex;  // Custom semaphore variables
} SharedMemory;

void wait(int *semaphore) {
    while (*semaphore <= 0);
    (*semaphore)--;
}

void signal(int *semaphore) {
    (*semaphore)++;
}

int main() {
    int fd = shm_open("pc_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(SharedMemory));
    SharedMemory *shm = (SharedMemory *)mmap(NULL, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    while (1) {
        wait(&shm->full);
        wait(&shm->mutex);

        int item = shm->buffer[shm->out];
        if (item == -1) {
            printf("Stopping consumption...\n");
            break;
        }

        printf("Consumed item: %d\n", item);
        shm->out = (shm->out + 1) % BUFFER_SIZE;

        signal(&shm->mutex);
        signal(&shm->empty);
    }

    munmap(shm, sizeof(SharedMemory));
    shm_unlink("pc_shm");
    return 0;
}

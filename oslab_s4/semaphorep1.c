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

    // Initialize semaphores in first execution
    shm->empty = BUFFER_SIZE;
    shm->full = 0;
    shm->mutex = 1;
    shm->in = 0;
    shm->out = 0;

    int item;
    while (1) {
        printf("Enter the item to be produced (-1 to stop): ");
        scanf("%d", &item);

        if (item == -1) {
            printf("Stopping production...\n");
            break;
        }

        wait(&shm->empty);
        wait(&shm->mutex);

        shm->buffer[shm->in] = item;
        printf("Produced item: %d\n", item);
        shm->in = (shm->in + 1) % BUFFER_SIZE;

        signal(&shm->mutex);
        signal(&shm->full);
    }

    munmap(shm, sizeof(SharedMemory));
    shm_unlink("pc_shm");
    return 0;
}

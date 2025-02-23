#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define SHM_SIZE sizeof(int)

int main() {
    int shm_fd = shm_open("matrix_shm", O_RDWR, S_IRUSR | S_IWUSR);

    int* sharedMatrix = (int*)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    int matrixSize;

    memcpy(&matrixSize, sharedMatrix, sizeof(int));

    int rows, columns;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    printf("Enter the number of columns: ");
    scanf("%d", &columns);
    if (rows * columns == matrixSize) {
        int matrixA[matrixSize];
        int matrixB[matrixSize];
        int resultMatrix[matrixSize];
        memcpy(matrixA, sharedMatrix + 1, matrixSize * sizeof(int));

        printf("Enter elements of matrix B:\n");
        for (int i = 0; i < matrixSize; i++) {
            printf("Enter element [%d][%d]: ", i / columns, i % columns);
            scanf("%d", &matrixB[i]);
        }

        for (int i = 0; i < matrixSize; i++) {
            resultMatrix[i] = matrixA[i] + matrixB[i];
        }

        printf("Sum Matrix:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                printf("%d ", resultMatrix[i * columns + j]);
            }
            printf("\n");
        }
    }
    else
     {
        printf("Matrix sizes do not match!\n");
     }

    munmap(sharedMatrix, SHM_SIZE);
    close(shm_fd);

    return 0;
}


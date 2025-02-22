//Write a program which creates a child process and the parent process
//waits for the child process to exit after printing the process id of the child and
//parent process. (Use: fork, wait, getpid, getppid, exit System Calls)
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    // Create child process using fork
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        exit(0);  // Exit the child process
    } else {
        // Parent process
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);

        // Wait for the child process to exit
        wait(NULL);
        printf("Child process has exited.\n");
    }

    return 0;
}


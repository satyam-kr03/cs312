#include <stdio.h>      // For printf, perror
#include <stdlib.h>     // For atoi, exit, EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>     // For fork, getpid, sleep
#include <sys/wait.h>   // For wait

int main(int argc, char *argv[]) {

    // 1. Validate Command-Line Arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        fprintf(stderr, "Where <N> is the number of child processes to create.\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Error: The number of children N must be a positive integer.\n");
        exit(EXIT_FAILURE);
    }

    printf("Parent process (PID %d) will create %d children.\n", getpid(), n);

    // 2. Fork N Child Processes
    for (int i = 0; i < n; i++) {
        pid_t rc = fork();

        if (rc < 0) {
            // Fork failed; exit
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (rc == 0) {
            // This is the child process
            printf("  -> Child (PID %d) created. Will sleep for 3 seconds.\n", getpid());
            
            // Use sleep so we have time to check the process status
            // from another terminal window using a command like `ps -f`
            sleep(3); 
            
            printf("  <- Child (PID %d) is finished.\n", getpid());
            exit(EXIT_SUCCESS); // Child exits here.
        }
        // The parent process continues the loop to create the next child.
    }

    // 3. Parent Reaps All Children
    printf("Parent (PID %d) is now waiting for all children to terminate.\n", getpid());
    for (int i = 0; i < n; i++) {
        pid_t child_pid = wait(NULL);
        if (child_pid > 0) {
            printf("Parent reaped child with PID %d.\n", child_pid);
        }
    }

    printf("Parent (PID %d) has reaped all children. Exiting.\n", getpid());

    return EXIT_SUCCESS;
}
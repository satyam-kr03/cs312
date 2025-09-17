// File: infinite_hello.c

#include <stdio.h>
#include <unistd.h> // Required for getpid() and sleep()
#include <fcntl.h>

int main() {
    // (a) Print the process id (pid)
    pid_t process_id = getpid();
    printf("Program starting with PID: %d\n", process_id);

    // Write a HelloWorld program with an infinite loop.
    while (1) {
        printf("Hello, World!\n");
        fflush(stdout); // Ensure the output is printed immediately
        sleep(1);       // Wait for 1 second
    }

    return 0; // This line is never reached
}
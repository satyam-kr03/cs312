// File: infinite_hello.c

#include <stdio.h>
#include <unistd.h> // Required for getpid() and sleep()
#include <fcntl.h>

double arr[1000000000];


int main() {
    pid_t process_id = getpid();
    printf("Program starting with PID: %d\n", process_id);

    for(int i = 0; i < 1000000000; i++) {
        arr[i] = i;
    }

    while (1) {
        printf("Hello, World!\n");
        sleep(2); // Sleep for 1 second to avoid flooding the output
    }

    return 0; // This line is never reached
}
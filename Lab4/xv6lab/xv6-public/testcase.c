// To run after making changes: make clean && make && make qemu-nox

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
  // Hello World
  // printf(1, "Hello, world!\n");

  // uptime() system call
  printf(1,"Uptime: %d\n", uptime());

  // start and execute a child process using fork(), wait() and exec() system calls
  int pid = fork();
  if(pid < 0){
    printf(1, "Fork failed\n");
  }
  else if(pid == 0){
    // Child process
    char *argv[] = { "echo", "Hello from child process!", 0 };
    exec("echo", argv);
    printf(1, "Exec failed\n");
    exit();
  } else {
    // Parent process
    wait();
    printf(1, "Child process completed\n");
  } 

  // Call the hello() system call
  hello();
  
  exit();
}


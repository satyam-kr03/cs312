#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "procInfo.h" // Include the header file with processInfo struct definition

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


// Hello world system call
int
sys_hello(void)
{
  cprintf("Hello, World!\n");
  return 0;
}

// Hello world system call with string argument
int
sys_helloStr(void)
{
  char *s;
  if(argstr(0, &s) < 0)
    return -1;
  cprintf("Hello, %s!\n", s);
  return 0;
}

// Get number of active processes
int
sys_getNumProc(void)
{
  return getNumProc();
}

// Get maximum PID assigned so far
int
sys_getMaxPid(void)
{ 
  return getMaxPid();
}

// Get process info by PID
int
sys_getProcInfo(void)
{
  int pid;
  struct processInfo* pinfo; 
  if(argint(0, &pid) < 0)
    return -1;
  if(argptr(1, (void*)&pinfo, sizeof(*pinfo)) < 0)
    return -1;
  return getProcInfo(pid, pinfo);
}
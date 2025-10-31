# cs312

Operating Systems

## Notes

### Lab 1

EOF signal is indicated by Ctrl+D. Alternatively, use an input file or piping using bash.

```
./charcount < somefile.txt
```

```
cat somefile.txt | ./charcount
```

Remember to compile with -lm flag to include math library

```bash
gcc printlog.c -o printlog -lm
```

### Lab 2

Header file stack.h gives the definition of the ADT.

These commands produce .o object files.

```bash
gcc -c arrstack.c
gcc -c llstack.c
```

To build the program:

```bash
gcc -o stackmain stackmain.c arrstack.o -DARRAY_STACK
gcc -o stackmain stackmain.c llstack.o
```

### Lab 3

ps command to look up info about a process, given it's name:

```bash
ps aux | grep "hello"
satyam    474098  0.0  0.0   2684  1408 pts/3    S+   10:15   0:00 ./hello
satyam    474267  0.0  0.0   9148  2176 pts/4    S+   10:16   0:00 grep --color=auto hello
```

ps command to show parent pid, command, and memory being used (RSS = Resident Set Size (KB)) :

```bash
ps -o pid,ppid,comm,rss 474098
    PID    PPID COMMAND           RSS
 474098   44351 hello            1408
```

The memory usage of the program will change if a large array is being accessed, not just with initialization.

The 0,1, and 2 files in the /proc/{pid}/fd directory are symbolic links to the stdin, stdout, stderr respectively.
The output file here won't be affected if we redirect the output of the program to a local file through the shell.

/proc/{pid}/fd/2 is still written to, but it doesn’t point to the terminal anymore — it points to the file you redirected into.

If you don’t redirect, /proc/{pid}/fd/2 continues to point to your tty device (e.g., /dev/pts/3).

```bash
(base) satyam@A514-56GM:/proc/485987/fd$ ls -l
total 0
lrwx------ 1 satyam satyam 64 Sep 18 10:37 0 -> /dev/pts/3
l-wx------ 1 satyam satyam 64 Sep 18 10:37 1 -> /home/satyam/Dev/cs312/Lab3/code/error.log
lr-x------ 1 satyam satyam 64 Sep 18 10:37 103 -> /usr/share/code/v8_context_snapshot.bin
lrwx------ 1 satyam satyam 64 Sep 18 10:37 2 -> /dev/pts/3
l-wx------ 1 satyam satyam 64 Sep 18 10:37 37 -> /home/satyam/.config/Code/logs/20250917T134331/ptyhost.log
lrwx------ 1 satyam satyam 64 Sep 18 10:37 38 -> /dev/ptmx
lrwx------ 1 satyam satyam 64 Sep 18 10:37 39 -> /dev/ptmx
lrwx------ 1 satyam satyam 64 Sep 18 10:37 40 -> /dev/ptmx
```

### Lab 4

![alt text](Lab4/q1.png)

```bash
make clean && make && make qemu-nox
```

To implement a new system call (simple ones like hello):

- Update user.h
- Update usys.S
- Update syscall.h
- Update syscall.c
- Implement the function in sysproc.c

Use cprintf to print to the console (in sysproc.c).

```c
cprintf("Hello, %s!\n", s);
```

Why no stdio.h in xv6 kernel code?

    stdio.h (and functions like printf) are part of the C standard library (glibc, musl, etc.).

    That library depends on system calls provided by an operating system (like Linux or Windows).

    But in the kernel itself (like xv6’s kernel), there is no libc — the kernel is the lowest layer.
    → So the kernel cannot use printf

In user programs in xv6

    User programs (those you write in user/) do have a small printf implementation.

    It’s a tiny, xv6-specific version, not full libc printf.

    Defined in user/ulib.c and user/printf.c.

    This user-level printf makes a write system call to print to file descriptors (e.g., fd = 1 for stdout).

To implement a new system call (dealing with processes):

- Update user.h
- Update usys.S
- Update syscall.h
- Update syscall.c
- Update sysproc.c with a dummy function
- Update [proc.h](Lab4/xv6lab/xv6-public/proc.h) to include new fields in struct if required.
- Implement the function in [proc.c](Lab4/xv6lab/xv6-public/proc.c)

```c
int
getNumProc(void)
{
  int count = 0;
  struct proc *p;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state != UNUSED)
      count++;
  }
  release(&ptable.lock);

  return count;
}
```

- Update defs.h

Use new header files to define new structs. ([procInfo.h](Lab4/xv6lab/xv6-public/procInfo.h))

Update the [Makefile](Lab4/xv6lab/xv6-public/Makefile) to run new programs ([testcase-procinfo.c](Lab4/xv6lab/xv6-public/testcase-procinfo.c))

### Lab 6

#### Virtual Address Space of a Program

```
Virtual Address Space (Page Size: 4096 bytes):
Start-End          Perms Offset   Device Inode Path
---------------------------------------------------
000060938f895000-000060938f896000 r--p 00000000 103:0         4 7375716                   /home/satyam/Documents/cs312/Lab6/q3 : 1 pages
000060938f896000-000060938f897000 r-xp 00001000 103:0         4 7375716                   /home/satyam/Documents/cs312/Lab6/q3 : 1 pages
000060938f897000-000060938f898000 r--p 00002000 103:0         4 7375716                   /home/satyam/Documents/cs312/Lab6/q3 : 1 pages
000060938f898000-000060938f899000 r--p 00002000 103:0         4 7375716                   /home/satyam/Documents/cs312/Lab6/q3 : 1 pages
000060938f899000-000060938f89a000 rw-p 00003000 103:0         4 7375716                   /home/satyam/Documents/cs312/Lab6/q3 : 1 pages
00006093a0958000-00006093a0979000 rw-p 00000000 00:00         0 [heap] : 33 pages
000072e448c00000-000072e448c28000 r--p 00000000 103:0         4 279812                    /usr/lib/x86_64-linux-gnu/libc.so.6 : 40 pages
000072e448c28000-000072e448db0000 r-xp 00028000 103:0         4 279812                    /usr/lib/x86_64-linux-gnu/libc.so.6 : 392 pages
000072e448db0000-000072e448dff000 r--p 001b0000 103:0         4 279812                    /usr/lib/x86_64-linux-gnu/libc.so.6 : 79 pages
000072e448dff000-000072e448e03000 r--p 001fe000 103:0         4 279812                    /usr/lib/x86_64-linux-gnu/libc.so.6 : 4 pages
000072e448e03000-000072e448e05000 rw-p 00202000 103:0         4 279812                    /usr/lib/x86_64-linux-gnu/libc.so.6 : 2 pages
000072e448e05000-000072e448e12000 rw-p 00000000 00:00         0 279812                    /usr/lib/x86_64-linux-gnu/libc.so.6 : 13 pages
000072e448e7c000-000072e448e7f000 rw-p 00000000 00:00         0 279812                    /usr/lib/x86_64-linux-gnu/libc.so.6 : 3 pages
000072e448e9f000-000072e448ea1000 rw-p 00000000 00:00         0 279812                    /usr/lib/x86_64-linux-gnu/libc.so.6 : 2 pages
000072e448ea1000-000072e448ea2000 r--p 00000000 103:0         4 279809                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 : 1 pages
000072e448ea2000-000072e448ecd000 r-xp 00001000 103:0         4 279809                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 : 43 pages
000072e448ecd000-000072e448ed7000 r--p 0002c000 103:0         4 279809                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 : 10 pages
000072e448ed7000-000072e448ed9000 r--p 00036000 103:0         4 279809                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 : 2 pages
000072e448ed9000-000072e448edb000 rw-p 00038000 103:0         4 279809                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 : 2 pages
00007fff80f80000-00007fff80fa2000 rw-p 00000000 00:00         0 [stack] : 34 pages
00007fff80fdc000-00007fff80fe0000 r--p 00000000 00:00         0 [vvar] : 4 pages
00007fff80fe0000-00007fff80fe2000 r-xp 00000000 00:00         0 [vdso] : 2 pages
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00         0 [vsyscall] : 1 pages
```

Explanation of the Output

The output displays the virtual address space of the running program (q3) by parsing maps, which lists memory mappings in the process's virtual memory. Each line represents a contiguous region (mapping) with:

Start-End: Hexadecimal virtual addresses (start inclusive, end exclusive).
Perms: Permissions (r=read, w=write, x=execute, p=private, s=shared).
Offset: File offset in the mapped file.
Device: Device number (major:minor).
Inode: Inode number of the file.
Path: File or description (e.g., [heap], [stack], library paths).
: X pages: Calculated number of pages in the mapping (size in bytes divided by page size, 4096 bytes).
Key regions include:

Program segments: Read-only data (r--p), executable code (r-xp), read-only code (r--p), writable data (rw-p) for q3.
Heap: Dynamic allocation area ([heap]).
Libraries: Shared libraries like libc.so.6 and ld-linux-x86-64.so.2.
Stack: Thread stack ([stack]).
Special mappings: [vvar], [vdso] (virtual dynamic shared object), [vsyscall] (legacy syscall interface).
Page counts are accurate for each mapping (e.g., a 4096-byte region = 1 page).

Verifying Correctness

To confirm the program is correct:

Compare to raw maps: Run cat /proc/self/maps in the terminal and match the addresses/permissions. The output should align exactly (except for the added page counts).
Check page size: Verify with getconf PAGESIZE (should be 4096). The program uses sysconf(\_SC_PAGESIZE) for this.
Validate calculations: For any mapping, compute (end - start) / 4096. Example: First mapping (0x60938f895000 - 0x60938f896000) = 0x1000 = 4096 bytes = 1 page.
Test parsing: Ensure sscanf correctly extracts fields (e.g., no buffer overflows). Run the program multiple times; output should be consistent.
Cross-check totals: Sum page counts across mappings (e.g., heap: 33 pages, stack: 34 pages). Use tools like pmap -p <pid> for comparison.
Error handling: If maps fails to open or page size query fails, the program exits with an error message, indicating issues.
If discrepancies arise, debug by adding prints for raw lines or parsed values. The program is Linux-specific and relies on proc filesystem availability.

#### Question 4

mmap() is a POSIX-compliant Unix system call that establishes a mapping between a process's address space and a file or other memory object. It is a fundamental mechanism for memory management and inter-process communication in many operating systems.
Key aspects of mmap():

    Memory-mapped files:
    mmap() allows a file or a portion of a file to be directly mapped into a process's virtual memory space. This means that the file's contents can be accessed as if they were part of the process's regular memory, eliminating the need for explicit read/write system calls for each access.
    Demand paging:
    File contents are not immediately loaded into physical RAM when mmap() is called. Instead, they are loaded on demand, meaning only the pages of the file that are actually accessed by the process are brought into memory. This optimizes memory usage.
    Shared memory:
    mmap() can be used to create shared memory regions, allowing multiple processes to access and modify the same memory area. This is a common method for inter-process communication.
    Anonymous mappings:
    mmap() can also create anonymous memory mappings, which are not backed by a file. These are often used for allocating large chunks of memory for data structures or for implementing dynamic memory allocation schemes.
    Protection flags:
    mmap() uses protection flags (e.g., PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE) to control the access permissions for the mapped memory region, enhancing security and preventing unauthorized access.
    Mapping flags:
    Various mapping flags (e.g., MAP_SHARED, MAP_PRIVATE, MAP_FIXED) control the behavior of the mapping, such as whether changes are visible to other processes, whether they are written back to the underlying file, and whether the mapping is placed at a specific address.

In essence, mmap() provides a powerful and efficient way to:

    Access file contents directly in memory.
    Share memory between processes.
    Allocate large memory regions.
    Manage memory with fine-grained control over access permissions and mapping behavior.

#### Question 5

https://stackoverflow.com/questions/30542428/does-malloc-use-brk-or-mmap
https://stackoverflow.com/questions/52869809/heap-break-does-not-change-after-malloc

The brk and sbrk system calls are fundamental low-level mechanisms in Unix-like operating systems used for managing a process's data segment, specifically the heap. They directly manipulate the "program break," which is the address of the first memory location beyond the end of the data segment.

1. brk():

   The brk() system call sets the program break to a specific address.
   Its signature is typically int brk(void \*addr);.
   If addr is greater than the current program break, the data segment is extended, and new memory is allocated.
   If addr is less than the current program break, the data segment is shrunk, and memory is deallocated.
   Upon success, brk() returns 0; otherwise, it returns -1 and sets errno.

2. sbrk():

   The sbrk() system call increments or decrements the program break by a specified amount.
   Its signature is typically void _sbrk(intptr_t increment);.
   increment specifies the number of bytes to add to the program break. A positive increment extends the data segment, while a negative increment shrinks it.
   sbrk() returns the previous value of the program break, which can be useful for determining the start of the newly allocated memory or for querying the current break by calling sbrk(0).
   If sbrk() fails, it returns (void _) -1.

Key characteristics and implications:

    Heap Management:
    brk and sbrk are the underlying system calls often used by higher-level memory allocation functions like malloc() and free() to manage the heap. However, modern malloc implementations may also use mmap() for larger allocations.
    Contiguous Memory:
    Memory allocated via brk and sbrk is typically contiguous within the process's virtual address space, forming the heap.
    Optimistic Allocation:
    In modern virtual memory systems, extending the program break doesn't immediately allocate physical memory. Physical pages are mapped only when a process attempts to access an unmapped virtual page, triggering a page fault.
    Direct Usage:
    Direct use of brk and sbrk is generally discouraged in application-level programming, as it's more complex and error-prone than using standard library functions like malloc(), calloc(), and free().
    Interaction with other memory functions:
    Using brk or sbrk in conjunction with other memory management functions (like malloc) can lead to undefined behavior, as they might interfere with each other's management of the heap.

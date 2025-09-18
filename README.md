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

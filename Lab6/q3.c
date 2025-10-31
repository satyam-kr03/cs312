#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *fp = fopen("/proc/self/maps", "r");
    if (fp == NULL) {
        perror("Error opening /proc/self/maps");
        return 1;
    }

    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size == -1) {
        perror("Error getting page size");
        fclose(fp);
        return 1;
    }

    printf("Virtual Address Space (Page Size: %ld bytes):\n", page_size);
    printf("Start-End          Perms Offset   Device Inode Path\n");
    printf("---------------------------------------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        unsigned long start, end;
        char perms[5], offset[9], device[6], inode[10], path[256];
        int items = sscanf(line, "%lx-%lx %4s %8s %5s %9s %255[^\n]",
                           &start, &end, perms, offset, device, inode, path);
        if (items >= 6) {
            unsigned long size = end - start;
            unsigned long num_pages = size / page_size;
            printf("%016lx-%016lx %4s %8s %5s %9s %s : %lu pages\n",
                   start, end, perms, offset, device, inode, path, num_pages);
        }
    }

    fclose(fp);
    return 0;
}
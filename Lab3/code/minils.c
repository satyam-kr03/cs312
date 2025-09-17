#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

// Struct to hold file information, needed for sorting by size.
struct file_info {
    char *name;
    off_t size; // from stat.st_size
};

// Comparison function for qsort to sort files by size in descending order.
int compare_by_size(const void *a, const void *b) {
    struct file_info *file_a = (struct file_info *)a;
    struct file_info *file_b = (struct file_info *)b;
    // For descending order, b->size comes before a->size
    return (file_b->size > file_a->size) - (file_b->size < file_a->size);
}

int main(int argc, char *argv[]) {
    // --- (b) Handle options -S and -1 ---
    int sort_by_size = 0;
    int one_per_line = 0;
    char *dir_path = "."; // Default to current directory

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            // It's an option
            if (strchr(argv[i], 'S')) {
                sort_by_size = 1;
            }
            if (strchr(argv[i], '1')) {
                one_per_line = 1;
            }
        } else {
            // It's a directory path
            dir_path = argv[i];
        }
    }

    DIR *dir = opendir(dir_path);

    // --- (c) Handle errors ---
    if (dir == NULL) {
        if (errno == EACCES) {
            fprintf(stderr, "minils: cannot open directory %s: Permission denied\n", dir_path);
        } else if (errno == ENOENT) {
            fprintf(stderr, "minils: cannot access %s: No such file or directory\n", dir_path);
        } else {
            // A generic error message for other potential issues
            perror("minils: opendir failed");
        }
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    struct file_info *files = NULL;
    int count = 0;
    int capacity = 10; // Initial capacity for the dynamic array

    files = malloc(capacity * sizeof(struct file_info));
    if (files == NULL) {
        perror("minils: malloc failed");
        closedir(dir);
        return EXIT_FAILURE;
    }

    // --- (a) Basic version using readdir ---
    while ((entry = readdir(dir)) != NULL) {
        // Ignore hidden files/directories like '.' and '..'
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Resize the dynamic array if needed
        if (count >= capacity) {
            capacity *= 2;
            struct file_info *temp = realloc(files, capacity * sizeof(struct file_info));
            if (temp == NULL) {
                perror("minils: realloc failed");
                // Free previously allocated memory before exiting
                for (int i = 0; i < count; i++) free(files[i].name);
                free(files);
                closedir(dir);
                return EXIT_FAILURE;
            }
            files = temp;
        }

        // Store the file name
        files[count].name = strdup(entry->d_name);
        if (files[count].name == NULL) {
            perror("minils: strdup failed");
            // Clean up and exit
             for (int i = 0; i < count; i++) free(files[i].name);
            free(files);
            closedir(dir);
            return EXIT_FAILURE;
        }
        files[count].size = 0; // Default size

        // If sorting by size, get the size using stat()
        if (sort_by_size) {
            struct stat file_stat;
            // Construct full path for stat()
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
            
            if (stat(full_path, &file_stat) == 0) {
                files[count].size = file_stat.st_size;
            } else {
                // Could print an error, but for ls, it's often better to just fail silently on stat
                // perror("minils: stat failed");
            }
        }
        count++;
    }

    closedir(dir);

    // If -S option is given, sort the array
    if (sort_by_size) {
        qsort(files, count, sizeof(struct file_info), compare_by_size);
    }

    // Print the directory contents
    for (int i = 0; i < count; i++) {
        printf("%s", files[i].name);
        if (one_per_line) {
            printf("\n");
        } else {
            // Add a tab for better spacing, mimics ls default behavior
            printf("\t"); 
        }
    }
    // Add a final newline if we weren't printing one per line and if there were files
    if (!one_per_line && count > 0) {
        printf("\n");
    }

    // Free all dynamically allocated memory
    for (int i = 0; i < count; i++) {
        free(files[i].name);
    }
    free(files);

    return EXIT_SUCCESS;
}

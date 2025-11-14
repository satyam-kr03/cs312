// Program 2: Main thread creates N threads, each prints its id, then main waits for all to finish
// Usage: ./thread_print N

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_func(void* arg) {
    int id = *(int*)arg;
    printf("I am thread %d\n", id);
    free(arg);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    pthread_t* threads = malloc(N * sizeof(pthread_t));
    for (int i = 0; i < N; ++i) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, thread_func, id);
    }
    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }
    printf("I am main thread and I am exiting\n");
    free(threads);
    return 0;
}

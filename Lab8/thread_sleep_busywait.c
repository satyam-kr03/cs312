// Program 3b: Busy-wait to ensure threads print in order 1..N
// Usage: ./thread_sleep_busywait N

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

volatile int turn = 1;

void* thread_func(void* arg) {
    int id = *(int*)arg;
    int r = (rand() % 10) + 1;
    sleep(r);
    // Busy-wait until it's this thread's turn
    while (turn != id) {}
    printf("Thread %d slept %d seconds\n", id, r);
    ++turn;
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
    srand(time(NULL));
    for (int i = 0; i < N; ++i) {
        int* id = malloc(sizeof(int));
        *id = i+1;
        pthread_create(&threads[i], NULL, thread_func, id);
    }
    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }
    free(threads);
    return 0;
}

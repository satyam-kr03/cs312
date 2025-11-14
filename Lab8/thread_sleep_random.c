// Program 3a: Each thread sleeps for r seconds (random 1-10), then prints its id
// Usage: ./thread_sleep N
// (a) Output order is due to both scheduler and random sleep time r

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void* thread_func(void* arg) {
    int id = *(int*)arg;
    int r = (rand() % 10) + 1; // random 1-10
    sleep(r);
    printf("Thread %d slept %d seconds\n", id, r);
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

/*
(a) The threads print their output in an order determined by both the scheduler and the random sleep time r. If r is the same for multiple threads, the scheduler decides which prints first. Otherwise, the thread with the smallest r will likely print first.
*/

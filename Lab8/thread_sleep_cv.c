// Program 3c: Use condition variables to ensure threads print in order 1..N
// Usage: ./thread_sleep_cv N

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int turn = 1;
pthread_mutex_t lock;
pthread_cond_t cond;

void* thread_func(void* arg) {
    int id = *(int*)arg;
    int r = (rand() % 10) + 1;
    sleep(r);
    pthread_mutex_lock(&lock);
    while (turn != id) {
        pthread_cond_wait(&cond, &lock);
    }
    printf("Thread %d slept %d seconds\n", id, r);
    ++turn;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
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
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    srand(time(NULL));
    for (int i = 0; i < N; ++i) {
        int* id = malloc(sizeof(int));
        *id = i+1;
        pthread_create(&threads[i], NULL, thread_func, id);
    }
    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    free(threads);
    return 0;
}

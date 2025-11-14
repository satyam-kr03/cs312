// Program 4: Synchronized round-robin printing 1,2,...,N,1,2,...,N, etc.
// Usage: ./round_robin_print N M
// N = number of threads, M = total numbers to print

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int N, M;
int current = 1;
int printed = 0;
pthread_mutex_t lock;
pthread_cond_t cond;

void* thread_func(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&lock);
        while (current != id && printed < M) {
            pthread_cond_wait(&cond, &lock);
        }
        if (printed >= M) {
            pthread_mutex_unlock(&lock);
            break;
        }
        printf("%d ", id);
        ++printed;
        current = (current % N) + 1;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
    free(arg);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s N M\n", argv[0]);
        return 1;
    }
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    pthread_t* threads = malloc(N * sizeof(pthread_t));
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    for (int i = 0; i < N; ++i) {
        int* id = malloc(sizeof(int));
        *id = i+1;
        pthread_create(&threads[i], NULL, thread_func, id);
    }
    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }
    printf("\n");
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    free(threads);
    return 0;
}

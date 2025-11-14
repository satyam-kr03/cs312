// Program 5: Barrier with semaphores and timing
// Usage: ./barrier_sem N
// Each thread increments a counter with random delay, barrier at multiples of 10

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/time.h>

#define MAX_THREADS 100

int N;
int counters[MAX_THREADS];
sem_t barrier_mutex, barrier_turnstile;
int barrier_count = 0;

void barrier() {
    sem_wait(&barrier_mutex);
    barrier_count++;
    if (barrier_count == N) {
        for (int i = 0; i < N-1; ++i) sem_post(&barrier_turnstile);
        barrier_count = 0;
        sem_post(&barrier_mutex);
    } else {
        sem_post(&barrier_mutex);
        sem_wait(&barrier_turnstile);
    }
}

void* thread_func(void* arg) {
    int id = *(int*)arg;
    struct timeval tv;
    for (int i = 1; i <= 10; ++i) {
        int r = (rand() % 3) + 1; // random 1-3 seconds
        sleep(r);
        counters[id]++;
        if (counters[id] % 10 == 0) {
            gettimeofday(&tv, NULL);
            printf("Thread %d reached %d at %ld.%06ld\n", id+1, counters[id], tv.tv_sec, tv.tv_usec);
            fflush(stdout);
            barrier();
        }
    }
    free(arg);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        return 1;
    }
    N = atoi(argv[1]);
    if (N > MAX_THREADS) N = MAX_THREADS;
    pthread_t threads[MAX_THREADS];
    sem_init(&barrier_mutex, 0, 1);
    sem_init(&barrier_turnstile, 0, 0);
    srand(time(NULL));
    for (int i = 0; i < N; ++i) counters[i] = 0;
    for (int i = 0; i < N; ++i) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, thread_func, id);
    }
    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&barrier_mutex);
    sem_destroy(&barrier_turnstile);
    return 0;
}

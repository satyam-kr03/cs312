// Program 1: Concurrent counter with three threads using condition variables
// Usage: ./counter N K
// T1 and T2 increment counter N times, T3 waits for counter to reach K

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
int N, K;
pthread_mutex_t lock;
pthread_cond_t cond;

void* incrementer(void* arg) {
    for (int i = 0; i < N; ++i) {
        pthread_mutex_lock(&lock);
        ++counter;
        pthread_cond_signal(&cond); // Wake up T3 if waiting
        pthread_mutex_unlock(&lock);
        usleep(10000); // Sleep 10ms to simulate work
    }
    return NULL;
}

void* watcher(void* arg) {
    pthread_mutex_lock(&lock);
    while (counter < K) {
        pthread_cond_wait(&cond, &lock);
    }
    printf("T3: Counter reached %d\n", K);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s N K\n", argv[0]);
        return 1;
    }
    N = atoi(argv[1]);
    K = atoi(argv[2]);
    pthread_t t1, t2, t3;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&t1, NULL, incrementer, NULL);
    pthread_create(&t2, NULL, incrementer, NULL);
    pthread_create(&t3, NULL, watcher, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Main: Final counter value = %d\n", counter);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}

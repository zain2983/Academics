#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

#define NUM_REPEATS 10
#define NUM_PRINTS 4

sem_t semaphore_a, semaphore_b, semaphore_c;

void generate_a() {
    for (int i = 0; i < NUM_PRINTS; i++) {
        sem_wait(&semaphore_a);
        printf("a");
        sem_post(&semaphore_b);
    }
}

void generate_b() {
    for (int i = 0; i < NUM_PRINTS; i++) {
        sem_wait(&semaphore_b);
        printf("b");
        sem_post(&semaphore_c);
    }
}

void generate_c() {
    for (int i = 0; i < NUM_PRINTS; i++) {
        sem_wait(&semaphore_c);
        printf("c");
        sem_post(&semaphore_a);
    }
}

int main() {
    sem_init(&semaphore_a, 0, 1);
    sem_init(&semaphore_b, 0, 0);
    sem_init(&semaphore_c, 0, 0);

    for (int i = 0; i < NUM_REPEATS; i++) {
        pid_t child_pid;
        child_pid = fork();

        if (child_pid == 0) {
            // Child process
                generate_a();
                generate_b();
                generate_c();
            exit(0);
        }
    }

    for (int i = 0; i < 3 * NUM_REPEATS; i++) {
        wait(NULL);  // Wait for all child processes to finish
    }

    sem_destroy(&semaphore_a);
    sem_destroy(&semaphore_b);
    sem_destroy(&semaphore_c);

    printf("\n");
    return 0;
}


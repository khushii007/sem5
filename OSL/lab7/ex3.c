#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t semaphore;    //global semaphore variable

void *func1 (void *param) {
    printf("Thread 1\n");
    sem_post(&semaphore);   //increments the value of semaphore
}

void *func2 (void *param) {
    sem_wait(&semaphore);
    printf("Thread 2\n");   //decrements the semaphore value if it's greater than 0 or else it will block until the value becomes greater than 0
}

int main() {
    pthread_t threads[2];
    sem_init (&semaphore, 0, 1);    //initialising the semaphore; o indicates that it is private to a single process; 1 indicates the value with which to initialise
    pthread_create(&threads[0], 0, func1, 0);
    pthread_create(&threads[1], 0, func2, 0);  
    pthread_join(threads[0], 0);
    pthread_join(threads[1], 0);
    sem_destroy(&semaphore);
}
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

int buf[5], f, r;
sem_t mutex, full, empty;

void *produce (void *arg) {
    for(int i=0; i<10; i++) {
        sem_wait(&empty);   //wait for buffer to have some empty slot ; decrements the count of empty slots
        sem_wait(&mutex);   //wait to access buffer (0 if unavailable)
        //gets access when mutex is more than 0
        //         ***critical region***
        printf("Produced item is %d\n", i);
        buf[(++r)%5] = i;   //add item to buffer
        sleep(1);
        //          ***critical region***
        sem_post(&mutex);    //release the buffer (1 for available)
        sem_post(&full);    //increments the count of full slots
        printf("full %u\n", full);
    }
}

void *consume (void *arg) {
    int item;
    for(int i=0; i<10; i++) {
        sem_wait(&full);    //wait for buffer to have some value in full; decrements the full slot by 1
        printf("Full %u\n", full);
        sem_wait(&mutex);   //wait to access to critical region
        item = buf[(++f)%5];    //consume item from buffer
        printf("Consumed item is %d\n", item);
        sleep(1);
        sem_post(&mutex);   //releases the mutex lock by incrementing back to 1
        sem_post(&empty);   //increment the empty slot count
    }
}

int main() {
    pthread_t tid1, tid2;
    sem_init (&mutex, 0, 1);    //initialising mutex to 1 for available
    sem_init (&full, 0, 0); //full slots in buffer (0 initially)
    sem_init (&empty, 0, 5);    //empty slots in buffer (5 initially)
    pthread_create (&tid1, 0, produce, 0);  //create producer thread
    pthread_create (&tid2, 0, consume, 0);  //create consumer thread
    pthread_join (tid1, 0); //wait for thread to finish
    pthread_join (tid2, 0); //wait for thread to finish
    return 0;
}
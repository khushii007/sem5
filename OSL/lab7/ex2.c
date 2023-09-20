#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;  //declaring a mutex variable "mutex"
volatile int counter=0; //"counter" value can change anytime 
//without explicitly changing its value in the code

void *count (void  *param) {
    for(int i=0; i<100; i++) {
        pthread_mutex_lock(&mutex); //acquiring a mutex lock
        //if the mutex is currently unowned, the calling thread 
        //successfully acquires the lock, and it can proceed to 
        //execute the code within the critical section protected 
        //by this mutex. If another thread already owns the mutex 
        //(i.e., it is locked), the calling thread will block and 
        //wait until the mutex becomes available.
        counter++;  //critical region
        printf("Count=%i\n", counter);  //critical region
        pthread_mutex_unlock(&mutex);   //releasing the mutex lock
    }
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, 0);  //initialising mutex with default attributes
    pthread_create(&thread1, 0, count, 0);
    pthread_create(&thread2, 0, count, 0);
    pthread_join(thread1, 0);   //wait for termination of thread1
    pthread_join(thread2, 0);
    pthread_mutex_destroy(&mutex);  //freeing the resources held by the mutex
    return 0;
}
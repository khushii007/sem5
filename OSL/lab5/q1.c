#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define QUEUE_SIZE 4
struct Queue {
    int buffer[QUEUE_SIZE];
    int front, rear, count;
};

void initializeQueue(struct Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

void enqueue(struct Queue* queue, int item) {
    if (queue->count < QUEUE_SIZE) {
        queue->rear = (queue->rear + 1) % QUEUE_SIZE;
        queue->buffer[queue->rear] = item;
        queue->count++;
    }
}

int dequeue(struct Queue* queue) {
    if (queue->count > 0) {
        int item = queue->buffer[queue->front];
        queue->front = (queue->front + 1) % QUEUE_SIZE;
        queue->count--;
        return item;
    } 
    else {
        return -1; // Queue is empty
    }
}

void* producer(void* arg) {
    struct Queue* queue = (struct Queue*)arg;
    for (int i = 1; i <= 4; i++) {
        enqueue(queue, i);
        printf("Produced: %d\n", i);
        sleep(1); // Simulate some work
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    struct Queue* queue = (struct Queue*)arg;
    for (int i = 0; i < 4; i++) {
        int item = dequeue(queue);
        if (item != -1) {
            printf("Consumed: %d\n", item);
        } 
        else {
            printf("Queue is empty.\n");
        }
        sleep(2); // Simulate some work
    }
    pthread_exit(NULL);
}

int main() {
    struct Queue queue;
    initializeQueue(&queue);
    pthread_t producerThread, consumerThread;
    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, &queue);
    pthread_create(&consumerThread, NULL, consumer, &queue);
    // Wait for the threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);
    return 0;
}
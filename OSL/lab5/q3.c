#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

int queue[MAX_SIZE];
int front = -1;
int rear = -1;

int isEmpty() {
    return (front == -1 && rear == -1);
}

int isFull() {
    return (rear == MAX_SIZE - 1);
}

void enqueue(int item) {
    if (isFull()) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    if (isEmpty()) {
        front = rear = 0;
    } 
    else {
        rear++; // Move the rear pointer to the next position
    }
    // Add the item to the rear of the queue
    queue[rear] = item;
    printf("Enqueued: %d\n", item);

}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    return 0;
}
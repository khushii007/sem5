#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 100 

struct threadData {
    int length;
    int *sequence;
    int odd;
    int even;
};

void *evenSum(void *arg) {
    struct threadData *data = (struct threadData*) arg;
    int length = data->length;
    int *sequence = data->sequence;
    data->even = 0;
    for(int i=0; i<length; i++) {
        if(sequence[i]%2 == 0) {
            data->even+=sequence[i];
        }
    }
    pthread_exit(NULL);
}

void *oddSum(void *arg) {
    struct threadData *data = (struct threadData*) arg;
    int length = data->length;
    int *sequence = data->sequence;
    data->odd = 0;
    for(int i=0; i<length; i++) {
        if(sequence[i]%2 != 0) {
            data->odd+=sequence[i];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if(argc!=2) {
        printf("\nUsage: %s <length>", argv[0]);
        return 1;
    }
    int length = atoi(argv[1]);
    if(length<=0 || length>100) {
        printf("\nLength limit between 1 and %d", MAX);
        return 1;
    }
    int sequence[MAX];
    printf("\nEnter numbers: ");
    for(int i=0; i<length; i++) {
        scanf("%d", &sequence[i]);
    }
    struct threadData data1;
    struct threadData data2;
    data1.length = length;
    data2.length = length;
    data1.sequence = sequence;
    data2.sequence = sequence;
    pthread_t tid1;
    pthread_t tid2;
    pthread_create(&tid1, NULL, evenSum, &data1);
    pthread_create(&tid2, NULL, oddSum, &data2);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("\nEven sum: %d", data1.even);
    printf("\nOdd sum: %d", data2.odd);
    return 0;
}
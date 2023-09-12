#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 100

struct threadData {
    int length;
    int *sequence;
    int result;
};

void *summation(void *arg) {
    struct threadData *data = (struct threadData*) arg;
    int length = data->length;
    int *sequence = data->sequence;
    data->result = 0;
    for(int i=0; i<length; i++) {
        if(sequence[i]>=0) {
            data->result+=sequence[i];
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
    if(length<=0 || length>MAX) {
        printf("\nLength limit between 1 and %d", MAX);
        return 1;
    }
    int sequence[MAX];
    for(int i=0; i<length; i++) {
        scanf("%d", &sequence[i]);
    }
    struct threadData data;
    data.length = length;
    data.sequence = sequence;
    pthread_t tid;
    pthread_create(&tid, NULL, summation, &data);
    pthread_join(tid, NULL);
    printf("Sum of non-negative numbers: %d", data.result);
    return 0;
}
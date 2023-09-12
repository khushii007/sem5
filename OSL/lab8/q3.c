#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 100

struct threadData {
    int *sequence;
    int start;
    int end;
    int count;
};

int isPrime(int n) {
    if(n<=1) {
        return 0;
    }
    for(int i=2; i*i<=n; i++) {
        if (n%i == 0) {
            return 0;
        }
    }
    return 1;
}

void *PrimeGen(void *arg) {
    struct threadData *data = (struct threadData*) arg;
    int *sequence = data->sequence;
    int start = data->start;
    int end = data->end;
    for(int i=start; i<=end; i++) {
        if(isPrime(i)) {
            sequence[data->count]=i;
            data->count++;
        }
    }
    sequence[data->count]='\0';
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if(argc!=3) {
        printf("\nUsage: %s <starting no> <ending no>", argv[0]);
        return 1;
    }
    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    int sequence[MAX];
    struct threadData data;
    data.sequence = sequence;
    data.start = start;
    data.end = end;
    data.count=0;
    pthread_t tid;
    pthread_create(&tid, NULL, PrimeGen, &data);
    pthread_join(tid, NULL);
    printf("\nPrime numbers: ");
    for(int i=0; i<data.count; i++) {
        printf("%d, ", sequence[i]);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 100

struct threadData {
    int length;     //no. of numbers to be generates
    int *sequence;      //stores memory address of first element of array
};

void *FiboGen(void *arg) {
    struct threadData *data = (struct threadData*) arg;     //converting void argument arg into a pointer to struct threadData and assigning it a variable name data
    int *sequence = data->sequence;
    int length  = data->length;
    sequence[0]=0;
    sequence[1]=1;
    for(int i=2; i<length; i++) {
        sequence[i]=sequence[i-1]+sequence[i-2];
    }
    pthread_exit (NULL);    //to exit thread execution
}

int main(int argc, char *argv[]) {
    if(argc!=2) {
        printf("\nUsage: %s <length>", argv[0]);
        return 1;
    }
    int length = atoi(argv[1]);     //argument is in ascii form so converting it to integer
    if(length<=0 || length>MAX) {
        printf("\nLength limit: 1 and %d", MAX);
        return 1;
    }
    int sequence[MAX];
    struct threadData data;
    data.sequence = sequence;
    data.length = length;
    pthread_t tid;      //creating thread identifier variable
    pthread_create(&tid, NULL, FiboGen, &data);     //creating a child thread by passing the variable data as an argument which executes the FiboGen function and stores the id in variable tid 
    pthread_join(tid, NULL);    //waiting for child thread to finish execution
    printf("\nFibonacci series: ");
    for(int i=0; i<length; i++) {
        printf("%d, ", sequence[i]);
    }
    return 0;
}
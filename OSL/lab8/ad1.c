#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 10

struct threadData {
    int (*mat1)[MAX];
    int (*mat2)[MAX];
    int (*res)[MAX];
    int r1, c1, c2;
};

void *matMul(void *arg) {
    struct threadData *data = (struct threadData*) arg;
    int (*mat1)[MAX] = data->mat1;
    int (*mat2)[MAX] = data->mat2;
    int (*res)[MAX] = data->res;
    int r1 = data->r1;
    int c1 = data->c1;
    int c2 = data->c2;
    for(int i=0; i<r1; i++) {
        for(int j=0; j<c2; j++) {
            res[i][j]=0;
            for(int k=0; k<c1; k++) {
                res[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    int r1, c1, r2, c2;
    printf("\n Enter row and column size for matrix 1: ");
    scanf("%d %d", &r1, &c1);
    printf("\n Enter row and column size for matrix 2: ");
    scanf("%d %d", &r2, &c2);
    if(r2!=c1) {
        printf("\nCannot be multiplied. (r2 should be equal to c1)");
        return 1;
    }

    printf("\nEnter values for matrix 1:");
    int mat1[MAX][MAX];
    for(int i=0; i<r1; i++) {
        for(int j=0; j<c1; j++) {
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("\nEnter values for matrix 2:");
    int mat2[MAX][MAX];
    for(int i=0; i<r2; i++) {
        for(int j=0; j<c2; j++) {
            scanf("%d", &mat2[i][j]);
        }
    }
    int res[MAX][MAX];
    struct threadData data;
    data.mat1 = mat1;
    data.mat2 = mat2;
    data.res = res;
    data.r1 = r1;
    data.c1 = c1;
    data.c2 = c2;
    pthread_t tid;
    pthread_create (&tid, NULL, matMul, &data);
    pthread_join(tid, NULL);
    printf("\nMatrix multiplication: \n");
    for(int i=0; i<r1; i++) {
        for(int j=0; j<c2; j++) {
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }
    return 0;
}
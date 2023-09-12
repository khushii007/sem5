#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 10

struct threadData {
    int row, col;
    //int row_sum, col_sum;
    int (*matrix)[MAX];
};

void *compute_row_sum (void *arg) {
    struct threadData *data = (struct threadData*) arg;
    int row = data->row;
    int col = data->col;
    int(*matrix)[MAX] = data->matrix;
    for(int i=0; i<row; i++) {
        int row_sum = 0;
        for(int j=0; j<col; j++) {
            row_sum+=matrix[i][j];
        }
        printf("\nRow %d sum: %d", i, row_sum);
    }
    pthread_exit(NULL);
}

void *compute_col_sum (void *arg) {
    struct threadData *data = (struct threadData*) arg;
    int row= data->row;
    int col = data->col;
    int (*matrix)[MAX] = data->matrix;
    for(int i=0; i<col; i++) {
        int col_sum=0;
        for(int j=0; j<row; j++) {
            col_sum+=matrix[j][i];
        }
        printf("\nCol %d sum: %d", i, col_sum);
    }
    pthread_exit(NULL);
}

int main() {
    int row, col;
    int matrix[MAX][MAX];
    printf("\nEnter row and column size: ");
    scanf("%d %d", &row, &col);
    printf("\nEnter matrix values: ");
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    struct threadData data;
    data.row = row;
    data.col = col;
    data.matrix = matrix;
    pthread_t tid1;
    pthread_t tid2;
    pthread_create (&tid1, NULL, compute_row_sum, &data);
    pthread_create (&tid2, NULL, compute_col_sum, &data);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
// credit to magicalbat on youtube
// https://www.youtube.com/watch?v=XSAIgL4bweE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE (1024)
#define TRIALS (1000)

struct matrix {
        int rows, cols;
        float *data;
};

static float mat_sum(struct matrix *mat) {
        float sum = 0.0f;

        for (int row = 0; row < mat->rows; row++) {
                for (int col = 0; col < mat->cols; col++) {
                        sum += mat->data[col + row * mat->cols];
                }
        }

        return sum;
}

int main(void) {
        struct matrix A;
        float sum = 0.0f;

        A.cols = SIZE;
        A.rows = SIZE;
        A.data = malloc(sizeof(float) * SIZE * SIZE);
        if (A.data == NULL) {
                fprintf(stderr, "failed to allocate matrix data\n");
                return 1;
        }

        for (int i = 0; i < SIZE * SIZE; i++) {
                A.data[i] = ((float) rand()) / RAND_MAX;
        }

        for (int i = 0; i < TRIALS; i++) {
                sum += mat_sum(&A);
        }

        printf("%.0f\n", sum);
        free(A.data);
        return 0;
}

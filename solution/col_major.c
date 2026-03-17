// Cache-unfriendly matrix multiply: j, k, i.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef SIZE
#define SIZE 256
#endif

struct matrix {
        int rows, cols;
        float *data;
};

static void init_matrix(struct matrix *mat) {
        mat->rows = SIZE;
        mat->cols = SIZE;
        mat->data = malloc(sizeof(float) * SIZE * SIZE);
        if (mat->data == NULL) {
                fprintf(stderr, "failed to allocate matrix data\n");
                exit(1);
        }

        for (int i = 0; i < SIZE * SIZE; i++) {
                mat->data[i] = ((float) rand()) / RAND_MAX;
        }
}

static void free_matrix(struct matrix *mat) {
        free(mat->data);
}

static float checksum(const struct matrix *mat) {
        float sum = 0.0f;

        for (int i = 0; i < mat->rows * mat->cols; i++) {
                sum += mat->data[i];
        }

        return sum;
}

static void mat_mul(struct matrix *out,
                    const struct matrix *a,
                    const struct matrix *b) {
        for (int i = 0; i < out->rows * out->cols; i++) {
                out->data[i] = 0.0f;
        }

        for (int j = 0; j < out->cols; j++) {
                for (int k = 0; k < a->cols; k++) {
                        for (int i = 0; i < out->rows; i++) {
                                out->data[j + i * out->cols] +=
                                        a->data[k + i * a->cols] *
                                        b->data[j + k * b->cols];
                        }
                }
        }
}

int main(void) {
        struct matrix a;
        struct matrix b;
        struct matrix out;

        init_matrix(&a);
        init_matrix(&b);
        init_matrix(&out);

        mat_mul(&out, &a, &b);
        printf("%.0f\n", checksum(&out));

        free_matrix(&a);
        free_matrix(&b);
        free_matrix(&out);
        return 0;
}

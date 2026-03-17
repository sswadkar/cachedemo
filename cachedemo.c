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

        // for col in B, for row in A
        // for row in A, for col in B
        for (int i = 0; i < a->rows; i++) {
                for (int k = 0; k < a->cols; k++) {
                        for (int j = 0; j < b->cols; j++) {
                                // a[i][k]
                                float a_ik = a->data[k + i * a->cols];
                                // b[k][j]
                                float b_kj = b->data[j + k * b->cols];
                                out->data[j + i * b->cols] += a_ik * b_kj;
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

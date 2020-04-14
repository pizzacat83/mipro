#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define NEW(p, n) {\
    (p) = malloc((n) * sizeof(p[0]));\
    if ((p) == NULL) {\
        puts("error in malloc");\
        exit(1);\
    }\
}

typedef double * Vec;
typedef Vec* Matrix;

Vec create_row_vector(int n) {
    Vec vec;
    NEW(vec, n);
    return vec;
}

Matrix create_matrix(int r, int c) {
    Vec* mat;

    NEW(mat, r);
    for (int i = 0; i < r; ++i) {
        mat[i] = create_row_vector(c);
    }

    return mat;
}

void delete_row_vector(Vec v) {
    free(v);
}

void delete_matrix(int r, int c, Matrix mat) {
    for(int i = 0; i < r; ++i) {
        delete_row_vector(mat[i]);
    }
    free(mat);
}

void read_matrix(int r, int c, Matrix mat) {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            double t;
            scanf("%lf", &t);
            mat[i][j] = t;
        }
    }
}

void print_matrix(int r, int c, Matrix mat) {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            printf("%f ", mat[i][j]);
        }
        printf("\n");
    }
}

Matrix transpose(int r, int c, Matrix mat) {
    Matrix matT = create_matrix(c, r);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            matT[j][i] = mat[i][j];
        }
    }

    return matT;
}

int main() {
    int r, c;
    scanf("%d %d", &r, &c);

    Matrix mat = create_matrix(r, c);
    read_matrix(r, c, mat);

    Matrix matT = transpose(r, c, mat);

    delete_matrix(r, c, mat);

    printf("%d %d\n", c, r);
    print_matrix(c, r, matT);

    delete_matrix(c, r, matT);

    return 0;
}

/* 
Samples
=======
In
--
2 3
1.0 2.5 -2
3.0 -4.0 1.5

Out
---
3 2
1.00 3.00 
2.50 -4.00 
-2.00 1.50 
*/

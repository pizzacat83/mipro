#include <map>
#include <vector>
#include <sys/time.h>
#include "../timer.h"

using namespace std;

typedef int_least16_t MatrixElement;
typedef map<size_t, MatrixElement> Row;

class MatrixM {
public:
    size_t r,c;
    vector<Row> rows;
};

MatrixM* new_matrix(size_t r, size_t c) {
    MatrixM* mat = new MatrixM();

    mat->r = r;
    mat->c = c;
    mat->rows.resize(c);
    return mat;
}

void delete_matrix(MatrixM* const mat) {
    delete mat;
}

void read_row(Row& row) {
    while (1) {
        int j1;
        scanf("%d", &j1);
        if (j1 == -1) {
            break;
        }
        size_t j = (size_t)(j1-1);
        double v;
        scanf("%lf", &v);
        row.insert(make_pair(j, (int)v));
    }
}

MatrixM* read_new_matrix() {
    size_t r, c;
    scanf("%ld %ld", &r, &c);
    MatrixM* mat = new_matrix(r, c);
    for (size_t i = 0; i < r; ++i) {
        read_row(mat->rows[i]);
    }
    return mat;
}

void print_matrix(const MatrixM& mat) {
    printf("%ld %ld\n", mat.r, mat.c);
    for (size_t i = 0; i < mat.r; ++i) {
        const Row& row = mat.rows[i];
        for(auto itr = begin(row); itr != begin(row); ++itr) {
            printf("%ld %d.000000 ", itr->first, itr->second);
        }
        printf("-1\n");
    }
}

bool product(const MatrixM& A, const MatrixM& B, MatrixM& AB) { // O(|nonzero(A)|*B.c + |nonzero(B)| * A.c)
#ifdef DEBUG
    if (A.c != B.r) {
        return false;
    }
#endif
    for (size_t i = 0; i < A.r; ++i) { // O(|nonzero(A)|*B.c + |nonzero(B)| * A.c)
        for(auto itr1 = begin(A.rows[i]); itr1 != end(A.rows[i]); ++itr1) { // O(|nonzero(a_i)||nonzero(b_k)|)
            size_t k = itr1->first;
            for(auto itr2 = begin(B.rows[k]); itr2 != end(B.rows[k]); ++itr2) { // O(|nonzero(b_k)|)
                size_t j = itr2->first;
                ++AB.rows[i][j];
            }
        }
    }
    return true;
}

// ----- main -----
int main() {
    tic();
    MatrixM* Ap = read_new_matrix(); // O(|nonzero(A)|)
    MatrixM& A = *Ap;
    toc(1);
    tic();
    MatrixM* A2p = new_matrix(A.r, A.c);
    MatrixM& A2 = *A2p;
    toc(2);
    tic();
    product(A, A, A2); // O(|nonzero(A)|*A.r)
    toc(3);
    tic();
    print_matrix(A2);
    toc(4);
    tic();
    delete_matrix(&A); // O(|nonzero(A)|)
    toc(5);
    tic();
    delete_matrix(&A2);
    toc(6);
    return 0;
}

/*
g++ code/omake/MatrixM.cpp -o code/omake/a.out -O3

10
=====
0.02user 0.00system 0:00.02elapsed 88%CPU (0avgtext+0avgdata 8320maxresident)k
0inputs+0outputs (0major+1533minor)pagefaults 0swaps

1: 9.023000 ms
2: 0.092000 ms
3: 6.904000 ms
4: 0.088000 ms
5: 0.301000 ms
6: 1.109000 ms
*/
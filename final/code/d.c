/**
 * D: loop i -> k -> j
 * Requirement: None
 * O(|nonzero(A)|*A.r)
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include "timer.h"

#define NEW(p, n) {\
    (p) = malloc((n) * sizeof(p[0]));\
    if ((p) == NULL) {\
        fprintf(stderr, "error in malloc (line #%d)\n", __LINE__);\
        exit(1);\
    }\
}

// ----- element -----

typedef double MatrixElement;

typedef struct {
    size_t j;
    MatrixElement value;
} Element;

bool isEqual(const Element* const a, const Element* const b) {
    return a->j == b->j && a->value == b->value;
}

void print_element(const Element* const element_p) {
    printf("%ld %lf", element_p->j + 1, element_p->value);
}

bool read_element(Element* element_p) {
    int j1;
    scanf("%d", &j1);
    if (j1 == -1) {
        return false;
    }
    element_p->j = (size_t)(j1-1);
    scanf("%lf", &(element_p->value));
    return true;
}

// ----- node -----

typedef struct Node_ {
    Element value;
    struct Node_* next;
} Node;

Node* new_node(const Element* const value_p) {
    Node* p;
    NEW(p, 1);
    p->value = *value_p;
    p->next = NULL;
    return p;
}

void delete_node(Node* const p) {
    free(p);
}

// ----- list -----

typedef struct {
    Node* head;
    Node* tail;
} List;

List create_empty_list() {
    List list;
    list.head = NULL;
    list.tail = NULL;
    return list;
}

void erase_front(List* const list_p) {
    Node* node_p = list_p->head;
    list_p->head = node_p->next;
    delete_node(node_p);
}

void clear_list(List* const list_p) {
    while (list_p->head != NULL) {
        erase_front(list_p);
    }
}

#define FOREACH(list, node_p) for (Node* (node_p) = (list).head; (node_p) != NULL; (node_p) = (node_p)->next)

void push_front(List* const list_p, Node* const node_p) {
    if (node_p->next != NULL) {
        // because overwriting node_p->next might cause memory leak
        fprintf(stderr, "pushed node is not NULL-ended\n");
        exit(1);
    }
    if (list_p->head == NULL) {
        // tail == NULL
        list_p->head = node_p;
        list_p->tail = node_p;
    } else {
        list_p->head = node_p;
    }
    node_p->next = list_p->head;
}

void push_back(List* const list_p, Node* const node_p) {
    if (node_p->next != NULL) {
        // because overwriting node_p->next might cause memory leak
        fprintf(stderr, "pushed node is not NULL-ended\n");
        exit(1);
    }
    if (list_p->tail == NULL) {
        // head == NULL
        list_p->head = node_p;
        list_p->tail = node_p;
    } else {
        list_p->tail->next = node_p;
        list_p->tail = node_p;
    }
}

void insert_node_after(List* const list_p, Node* const parent_p, Node* const child_p) {
    if (child_p->next != NULL) {
        // because overwriting child_p->next might cause memory leak
        fprintf(stderr, "inserteded node is not NULL-ended\n");
        exit(1);
    }
    if (parent_p->next == NULL) {
        // update tail
        list_p->tail = child_p;
    }
    child_p->next = parent_p->next;
    parent_p->next = child_p;
}

void print_list(List list) {
    FOREACH(list, node_p) {
        print_element(&(node_p->value));
        printf(" ");
    }
    printf("-1\n");
}

void read_list(List* const list_p) {
    *list_p = create_empty_list();
    while (1) {
        Element element;
        bool ok = read_element(&element);
        if (!ok) {
            break;
        }
        push_back(list_p, new_node(&element));
    }
}

Node* search(List list, const Element* const q_p) {
    FOREACH (list, node_p) {
        if (isEqual(&(node_p->value), q_p)) {
            return node_p;
        }
    }
    return NULL;
}

// ----- matrix -----

typedef struct {
    size_t r;
    size_t c;
    List* rows;
} MatrixS;

MatrixS new_matrix(size_t r, size_t c) {
    MatrixS mat;
    mat.r = r;
    mat.c = c;
    mat.rows = NULL;
    if (r > 0) {
        NEW(mat.rows, r);
        for (size_t i = 0; i < r; ++i) {
            mat.rows[i] = create_empty_list();
        }
    }
    return mat;
}

void clear_matrix(MatrixS* const mat) {
    for (size_t i = 0; i < mat->r; ++i) {
        clear_list(&(mat->rows[i]));
    }
    free(mat->rows);
    mat->rows = NULL;
}

MatrixS read_matrix() {
    size_t r, c;
    scanf("%ld %ld", &r, &c);
    MatrixS mat = new_matrix(r, c);
    for (size_t i = 0; i < r; ++i) {
        read_list(&(mat.rows[i]));
    }
    return mat;
}

void print_matrix(MatrixS mat) {
    printf("%ld %ld\n", mat.r, mat.c);
    for (size_t i=0; i < mat.r; ++i) {
        print_list(mat.rows[i]);
    }
}

MatrixS transpose(MatrixS mat) {
    // O(|E|)
    MatrixS matT = new_matrix(mat.c, mat.r);
    for (size_t i=0; i < mat.r; ++i) {
        FOREACH(mat.rows[i], node_p) {
            push_back(&matT.rows[node_p->value.j], new_node(&(Element){i, node_p->value.value}));
        }
    }
    return matT;
}

MatrixElement dot(List v1, List v2) {
    // O(|nonzero(v1)| + |nonzero(v2)|)
    const Node* np1 = v1.head;
    const Node* np2 = v2.head;
    MatrixElement res = 0;
    while (np1 != NULL && np2 != NULL) {
        if (np1->value.j == np2->value.j) {
            res += np1->value.value * np2->value.value;
            np1 = np1->next;
            np2 = np2->next;
        } else if (np1->value.j < np2->value.j) {
            np1 = np1->next;
        } else {
            np2 = np2->next;
        }
    }
    return res;
}

// ----- dense matrix -----
typedef struct {
    size_t r,c;
    MatrixElement** rows;
} MatrixD;

MatrixD new_dense_matrix(size_t r, size_t c) {
    MatrixD mat;
    mat.r = r;
    mat.c = c;
    NEW(mat.rows, r);
    for (size_t i = 0; i < r; ++i) {
        NEW(mat.rows[i], c);
        for (size_t j = 0; j < c; ++j) {
            mat.rows[i][j] = 0;
        }
    }
    return mat;
}

void print_dense_matrix(MatrixD mat) {
    printf("%ld %ld\n", mat.r, mat.c);
    for (size_t i = 0; i < mat.r; ++i) {
        for (size_t j = 0; j < mat.c; ++j) {
            if (mat.rows[i][j] != 0) {
                printf("%ld %lf ", j + 1, mat.rows[i][j]);
            }
        }
        printf("-1\n");
    }
}

void clear_dense_matrix(MatrixD* const mat) {
    for (size_t i = 0; i < mat->r; ++i) {
        free(mat->rows[i]);
    }
    free(mat->rows);
    mat->rows = NULL;
}


bool product(MatrixS A, MatrixS B, MatrixD AB) { // O(|nonzero(A)|*B.c + |nonzero(B)| * A.c)
    if (A.c != B.r) {
        return false;
    }
    for (size_t i = 0; i < A.r; ++i) { // O(|nonzero(A)|*B.c + |nonzero(B)| * A.c)
        FOREACH(A.rows[i], n1p) { // O(|nonzero(a_i)||nonzero(b_k)|)
            size_t k = n1p->value.j;
            double Aik = n1p->value.value;
            FOREACH(B.rows[k], n2p) { // O(|nonzero(b_k)|)
                size_t j = n2p->value.j;
                double Bkj = n2p->value.value;
                AB.rows[i][j] += Aik * Bkj;
            }
        }
    }
    return true;
}


// ----- main -----
int main() {
    tic();
    MatrixS A = read_matrix(); // O(|nonzero(A)|)
    toc(1);
    tic();
    MatrixD A2 = new_dense_matrix(A.r, A.c);
    toc(2);
    tic();
    product(A, A, A2); // O(|nonzero(A)|*A.r)
    toc(3);
    tic();
    print_dense_matrix(A2);
    toc(4);
    tic();
    clear_matrix(&A); // O(|nonzero(A)|)
    toc(5);
    tic();
    clear_dense_matrix(&A2);
    toc(6);
    return 0;
}

/* 
Samples
=======
In
--
3 2
1 2.0 -1
2 4.0 -1
2 1.0 -1
2 4
1 3.0 4 1.0 -1
2 4.0 3 2.0 4 3.0 -1

Out
---
3 4
1 6.0 4 2.0 -1
2 16.0 3 8.0 4 12.0 -1
2 4.0 3 2.0 4 3.0 -1

*/

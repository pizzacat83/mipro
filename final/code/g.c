/**
 * D: loop i -> k -> j
 * Requirement: binary
 * O(|nonzero(A)|*A.r)
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "timer.h"

#define NEW(p, n) {\
    (p) = malloc((n) * sizeof(p[0]));\
}

// ----- element -----

typedef int MatrixElement;

typedef struct {
    size_t j;
    int value;
} Element;

bool isEqual(const Element* const a, const Element* const b) {
    return a->j == b->j && a->value == b->value;
}

void print_element(const Element* const element_p) {
    printf("%ld %d.000000", element_p->j + 1, element_p->value);
}

bool read_element(Element* element_p) {
    int j1;
    scanf("%d", &j1);
    if (j1 == -1) {
        return false;
    }
    element_p->j = (size_t)(j1-1);
    double v;
    scanf("%lf", &v);
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
#ifdef DEBUG
    if (node_p->next != NULL) {
        // because overwriting node_p->next might cause memory leak
        fprintf(stderr, "pushed node is not NULL-ended\n");
        exit(1);
    }
#endif
    if (list_p->head == NULL) {
        // tail == NULL
        list_p->head = node_p;
        list_p->tail = node_p;
    } else {
        node_p->next = list_p->head;
        list_p->head = node_p;
    }
}

void push_back(List* const list_p, Node* const node_p) {
#ifdef DEBUG
    if (node_p->next != NULL) {
        // because overwriting node_p->next might cause memory leak
        fprintf(stderr, "pushed node is not NULL-ended\n");
        exit(1);
    }
#endif
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
#ifdef DEBUG
    if (child_p->next != NULL) {
        // because overwriting child_p->next might cause memory leak
        fprintf(stderr, "inserted node is not NULL-ended\n");
        exit(1);
    }
#endif
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
#ifdef DEBUG
    if (r > 0) {
#endif
        NEW(mat.rows, r);
        for (size_t i = 0; i < r; ++i) {
            mat.rows[i] = create_empty_list();
        }
#ifdef DEBUG
    }
#endif
    return mat;
}

void clear_matrix(MatrixS* const mat) {
    for (size_t i = 0; i < mat->r; ++i) {
        clear_list(&(mat->rows[i]));
    }
    free(mat->rows);
#ifdef DEBUG
    mat->rows = NULL;
#endif
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

// MatrixS transpose(MatrixS mat) {
//     // O(|E|)
//     MatrixS matT = new_matrix(mat.c, mat.r);
//     for (size_t i=0; i < mat.r; ++i) {
//         FOREACH(mat.rows[i], node_p) {
//             push_back(&matT.rows[node_p->value.j], new_node(&(Element){i}));
//         }
//     }
//     return matT;
// }

// MatrixElement dot(List v1, List v2) {
//     // O(|nonzero(v1)| + |nonzero(v2)|)
//     const Node* np1 = v1.head;
//     const Node* np2 = v2.head;
//     MatrixElement res = 0;
//     while (np1 != NULL && np2 != NULL) {
//         if (np1->value.j == np2->value.j) {
//             res += np1->value.value * np2->value.value;
//             np1 = np1->next;
//             np2 = np2->next;
//         } else if (np1->value.j < np2->value.j) {
//             np1 = np1->next;
//         } else {
//             np2 = np2->next;
//         }
//     }
//     return res;
// }

bool product(MatrixS A, MatrixS B, const MatrixS* AB) { // O(|nonzero(A)|*B.c + |nonzero(B)| * A.c)
#ifdef DEBUG
    if (A.c != B.r) {
        return false;
    }
#endif
    for (size_t k = 0; k < A.r; ++k) { // O(|nonzero(A)|*B.c + |nonzero(B)| * A.c)
        FOREACH(A.rows[k], n1p) { // O(|nonzero(a_i)||nonzero(b_k)|)
            size_t i = n1p->value.j;
            Node* abij_p = AB->rows[i].head;
            FOREACH(B.rows[k], n2p) { // O(|nonzero(b_k)|)
                size_t j = n2p->value.j;
                if (abij_p == NULL || abij_p->value.j > j) {
                    abij_p = new_node(&(Element){j, 1});
                    push_front(&AB->rows[i], abij_p);
                    continue;
                }

                while (1) {
                    if (abij_p->value.j == j) {
                        ++(abij_p->value.value);
                        break;
                    }
                    if (abij_p->next == NULL) {
                        abij_p = new_node(&(Element){j, 1});
                        push_back(&AB->rows[i], abij_p);
                        break;
                    }
                    if (abij_p->next->value.j > j) {
                        Node* abij_np = new_node(&(Element){j, 1});
                        insert_node_after(&AB->rows[i], abij_p, abij_np);
                        break;
                    }
                    abij_p = abij_p->next;
                }
            }
        }
    }
    return true;
}

// ----- main -----
int main() {
    // List l = create_empty_list();
    // for (size_t i = 0; i < 10; ++i) {
    //     push_front(&l, new_node(&(Element){i, 0.0}));
    //     print_list(l);
    // }
    // clear_list(&l);
    tic();
    MatrixS A = read_matrix(); // O(|nonzero(A)|)
    toc(1);
    tic();
    MatrixS A2 = new_matrix(A.r, A.c);
    toc(2);
    tic();
    product(A, A, &A2); // O(|nonzero(A)|*A.r)
    toc(3);
    tic();
    print_matrix(A2);
    toc(4);
    tic();
    clear_matrix(&A); // O(|nonzero(A)|)
    toc(5);
    tic();
    clear_matrix(&A2);
    toc(6);
    return 0;
}

/* 
timer
=======
1: 12.981000 ms
2: 44.121000 ms
3: 7.003000 ms
4: 45.103000 ms
5: 0.671000 ms
6: 0.823000 ms

*/

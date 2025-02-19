#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

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

void push_front(List* const list_p, const Element* const element_p) {
    Node* node_p = new_node(element_p);
    if (list_p->head == NULL) {
        // tail == NULL
        list_p->head = node_p;
        list_p->tail = node_p;
    } else {
        list_p->head = node_p;
    }
    node_p->next = list_p->head;
}

void push_back(List* const list_p, const Element* const element_p) {
     Node* node_p = new_node(element_p);
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
        push_back(list_p, &element);
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

MatrixS create_empty_matrix(size_t r, size_t c) {
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
    MatrixS mat = create_empty_matrix(r, c);
    for (size_t i = 0; i < r; ++i) {
        read_list(&mat.rows[i]);
    }
    return mat;
}

MatrixS create_identity_matrix(size_t n) {
    MatrixS mat = create_empty_matrix(n,n);
    for (size_t i = 0; i < n; ++i) {
        push_back(&mat.rows[i], &(Element){ j: i, value: 1 });
    }
    return mat;
}

MatrixS clone_matrix(MatrixS mat) {
    MatrixS mat2 = create_empty_matrix(mat.r, mat.c);
    for (size_t i = 0; i < mat.r; ++i) {
        FOREACH(mat.rows[i], np) {
            push_back(&mat2.rows[i], &np->value);
        }
    }
    return mat2;
}

void print_matrix(MatrixS mat) {
    printf("%ld %ld\n", mat.r, mat.c);
    for (size_t i=0; i < mat.r; ++i) {
        print_list(mat.rows[i]);
    }
}

MatrixS transpose(MatrixS mat) {
    // O(|E|)
    MatrixS matT = create_empty_matrix(mat.c, mat.r);
    for (size_t i=0; i < mat.r; ++i) {
        FOREACH(mat.rows[i], node_p) {
            push_back(&matT.rows[node_p->value.j], &(Element){i, node_p->value.value});
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

MatrixS product(MatrixS A, MatrixS B) {
    if (A.c != B.r) {
        return create_empty_matrix(0, 0);
    }
    MatrixS BT = transpose(B); // O(|B_E|)
    MatrixS AB = create_empty_matrix(A.r, B.c);
    for (size_t i = 0; i < A.r; ++i) { // O(|A_E|*B.c + |B_E| * A.c)
        for(size_t j = 0; j < BT.r; ++j) { // O(|nonzero(ai)|*B.c + |B_E|)
            MatrixElement x = dot(A.rows[i], BT.rows[j]); // O(|nonzero(ai)| + |nonzero(bj)|)
            if (x != 0) {
                push_back(&(AB.rows[i]), &(Element) {j: j, value: x});
            }
        }
    }
    clear_matrix(&BT); // O(|B_E|)
    return AB;
}

MatrixS power(MatrixS A, unsigned n) {
    if (A.r != A.c) {
        return create_empty_matrix(0, 0);
    }
    int maxk = 0;
    while(n>>maxk) {
        maxk+=1;
    }
    MatrixS res = create_identity_matrix(A.r);
    MatrixS A_2_k = clone_matrix(A);
    for(int k = 0; k < maxk; ++k) {
        if ((n >> k) & 1) {
            MatrixS res_new = product(res, A_2_k);
            clear_matrix(&res);
            res = res_new;
        }
        MatrixS A_2_k_new = product(A_2_k, A_2_k);
        clear_matrix(&A_2_k);
        A_2_k = A_2_k_new;
    }
    clear_matrix(&A_2_k);
    return res;
}

// ----- main -----

int main() {
    MatrixS A = read_matrix();
    unsigned n;
    scanf("%d", &n);
    MatrixS A_n = power(A, n);
    print_matrix(A_n);
    clear_matrix(&A);
    clear_matrix(&A_n);
    return 0;
}

/* 
Samples
=======
In
--
2 2
1 2.0 -1
2 3.0 -1
5

Out
---
2 2
1 32.0 -1
2 243.0 -1
*/

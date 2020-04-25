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

typedef struct {
    size_t j;
    double value;
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

Node* new_node(Element value) {
    Node* p;
    NEW(p, 1);
    p->value = value;
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
        push_back(list_p, new_node(element));
    }
}

Node* search(List list, Element q) {
    FOREACH (list, node_p) {
        if (isEqual(&(node_p->value), &q)) {
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
    NEW(mat.rows, r);
    for (size_t i = 0; i < r; ++i) {
        mat.rows[i] = create_empty_list();
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
    MatrixS matT = create_empty_matrix(mat.c, mat.r);
    for (size_t i=0; i < mat.r; ++i) {
        FOREACH(mat.rows[i], node_p) {
            push_back(&matT.rows[node_p->value.j], new_node((Element){i, node_p->value.value}));
        }
    }
    return matT;
}

// ----- main -----

int main() {
    MatrixS mat = read_matrix();
    MatrixS matT = transpose(mat);
    print_matrix(matT);
    clear_matrix(&mat);
    clear_matrix(&matT);
    return 0;
}

/* 
Samples
=======
In
--
5 5
1 1.0 2 2.0 -1
1 2.0 2 1.0 3 2.0 -1
2 2.0 3 1.0 -1
4 1.0 -1
5 1.0 -1

Out
---
5 5
1 1.0 2 2.0 -1
1 2.0 2 1.0 3 2.0 -1
1 2.0 3 1.0 -1
4 1.0 -1
5 1.0 -1
*/

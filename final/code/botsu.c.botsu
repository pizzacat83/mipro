/**
 * botsu: 入力をslist, 出力をHashで持とうとして破滅した
 * C言語にメソッドの概念かオーバーロードの概念があればいいのに
 * Requirement: None
 * O(?)
 */

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

typedef size_t HashKey;
typedef double HashValue;

typedef struct {
    HashKey k;
    HashValue v;
} Element;

bool isEqual(const Element* const a, const Element* const b) {
    return a->k == b->k && a->v == b->v;
}

void print_element(const Element* const element_p) {
    printf("%ld %lf", element_p->k, element_p->v);
}

bool read_element(Element* element_p) {
    int j1;
    scanf("%d", &j1);
    if (j1 == -1) {
        return false;
    }
    element_p->k = (size_t)(j1-1);
    scanf("%lf", &element_p->v);
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
        push_back(list_p, new_node(&element));
    }
}

Node* search_list(List list, const Element* const q_p) {
    FOREACH (list, node_p) {
        if (isEqual(&(node_p->value), q_p)) {
            return node_p;
        }
    }
    return NULL;
}

// ----- Hash -----

typedef struct {
    size_t slots_len;
    List* slots;
} Hash;

size_t key_to_index(Hash hash, HashKey k) {
    return k % hash.slots_len;
}

Hash create_empty_hash(size_t slots_len) {
    Hash hash;
    hash.slots_len = slots_len;
    hash.slots = NULL;
    if (slots_len > 0) {
        NEW(hash.slots, slots_len);
        for (size_t i = 0; i < slots_len; ++i) {
            hash.slots[i] = create_empty_list();
        }
    }
    return hash;
}

void clear_hash(Hash* const hash) {
    for (size_t i = 0; i < hash->slots_len; ++i) {
        clear_list(&(hash->slots[i]));
    }
    free(hash->slots);
    hash->slots = NULL;
}

void add_hash(Hash const* hp, const Element* const ep) {
    push_back(&hp->slots[key_to_index(*hp, ep->k)], ep);
}

// Hash read_hash(size_t slots_len) {
//     size_t n;
//     scanf("%ld", &n);
//     Hash hash = create_empty_hash(slots_len);
//     for (size_t i = 0; i < n; ++i) {
//         Element e = read_element();
//         add_hash(&hash, &e);
//     }
//     return hash;
// }

Node* search_list_key(List list, HashKey k) {
    FOREACH (list, node_p) {
        if (node_p->value.k == k) {
            return node_p;
        }
    }
    return NULL;
}

HashValue* search_hash(Hash hash, HashKey k) {
    Node* res = search_list_key(hash.slots[key_to_index(hash, k)], k);
    if (res == NULL) {
        return NULL;
    } else {
        return &res->value.v;
    }
}

// ----- matrix -----

typedef struct {
    size_t r;
    size_t c;
    Hash* rows;
} MatrixH;

const int HASH_SLOT_SIZE = 32;

MatrixH create_empty_matrix(size_t r, size_t c) {
    MatrixH mat;
    mat.r = r;
    mat.c = c;
    mat.rows = NULL;
    if (r > 0) {
        NEW(mat.rows, r);
        for (size_t i = 0; i < r; ++i) {
            mat.rows[i] = create_empty_hash(HASH_SLOT_SIZE);
        }
    }
    return mat;
}

void clear_matrix(MatrixH* const mat) {
    for (size_t i = 0; i < mat->r; ++i) {
        clear_list(&(mat->rows[i]));
    }
    free(mat->rows);
    mat->rows = NULL;
}

MatrixH read_matrix() {
    size_t r, c;
    scanf("%ld %ld", &r, &c);
    MatrixH mat = create_empty_matrix(r, c);
    for (size_t i = 0; i < r; ++i) {
        read_list(&(mat.rows[i]));
    }
    return mat;
}

void print_matrix(MatrixH mat) {
    printf("%ld %ld\n", mat.r, mat.c);
    for (size_t i=0; i < mat.r; ++i) {
        print_hash(mat.rows[i]);
    }
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

MatrixH product(MatrixH A, MatrixH B) { // O(|nonzero(A)|*B.c + |nonzero(B)| * A.c)
    if (A.c != B.r) {
        return create_empty_matrix(0, 0);
    }
    MatrixH AB = create_empty_matrix(A.r, B.c);
    for (size_t i = 0; i < A.r; ++i) { // O(|nonzero(A)|*B.c + |nonzero(B)| * A.c)
        FOREACH(A.rows[i], n1p) {
            size_t k = n1p->value.j;
            double Aik = n1p->value.value;
            FOREACH(A.rows[k], n2p) {
                size_t j = n2p->value.j;
                double Akj = n2p->value.value;

            }
        }
        for(size_t j = 0; j < BT.r; ++j) { // O(|nonzero(ai)|*B.c + |nonzero(B)|)
            MatrixElement x = dot(A.rows[i], BT.rows[j]); // O(|nonzero(ai)| + |nonzero(bj)|)
            if (x != 0) {
                push_back(&(AB.rows[i]), new_node(&(Element) {j: j, value: x}));
            }
        }
    }
    clear_matrix(&BT); // O(|nonzero(B)|)
    return AB;
}

// ----- main -----

int main() {
    MatrixH A = read_matrix(); // O(|nonzero(A)|)
    MatrixH A2 = product(A, A); // O(|nonzero(A)|*A.r)
    print_matrix(A2); // O(|nonzero(A)|)
    clear_matrix(&A); // O(|nonzero(A)|)
    clear_matrix(&A2); // O(|nonzero(A)|)
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

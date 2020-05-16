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

Element read_element() {
    Element e;
    scanf("%ld %lf", &e.k, &e.v);
    return e;
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
    size_t n;
    List* slots;
} Hash;

size_t key_to_index(Hash hash, HashKey k) {
    return k % hash.slots_len;
}

Hash create_empty_hash(size_t slots_len) {
    Hash hash;
    hash.slots_len = slots_len;
    hash.n = 0;
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

Hash read_hash(size_t slots_len) {
    size_t n;
    scanf("%ld", &n);
    Hash hash = create_empty_hash(slots_len);
    for (size_t i = 0; i < n; ++i) {
        Element e = read_element();
        add_hash(&hash, &e);
    }
    return hash;
}

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

// void print_matrix(MatrixS mat) {
//     printf("%ld %ld\n", mat.r, mat.c);
//     for (size_t i=0; i < mat.r; ++i) {
//         print_list(mat.rows[i]);
//     }
// }


// ----- main -----

int main() {
    size_t slots_len = 1000;
    Hash hash = read_hash(slots_len);
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        HashKey k;
        scanf("%ld", &k);
        HashValue* res = search_hash(hash, k);
        if (res == NULL) {
            printf("-1\n");
        } else {
            printf("%ld %f\n", k, *res);
        }
    }
    clear_hash(&hash);
    return 0;
}

/* 
Samples
=======
In
--
4
1 2.0
2 4.0
3 6.0
5 10.0
3
3
4
1

Out
---
6.0
-1
2.0

*/

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

typedef int Element;

typedef struct Node_ {
    Element value;
    struct Node_* next;
} Node;

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
    }
    list_p->tail = node_p;
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

#define FOREACH(list, node_p) for (Node* (node_p) = (list).head; (node_p) != NULL; (node_p) = (node_p)->next)

Node* search(List list, Element q) {
    FOREACH (list, node_p) {
        if (node_p->value == q) {
            return node_p;
        }
    }
    return NULL;
}

Node* search_sorted_parent(List list, Element q) {
    FOREACH (list, node_p) {
        if (node_p->value <= q && (node_p->next == NULL || q <= node_p->next->value)) {
            return node_p;
        }
    }
    return NULL;
}

void print_list(List list) {
    FOREACH(list, node_p) {
        printf("%d ", node_p->value);
    }
    printf("-1\n");
}

List read_list(bool reversed) {
    List list = create_empty_list();
    while (1) {
        int value;
        scanf("%d", &value);
        if (value == -1) break;
        Node* node_p = new_node(value);
        (reversed ? push_front : push_back)(&list, node_p);
    }
    return list;
}

int main() {
    List list = read_list(false);
    print_list(list);
    clear_list(&list);
    return 0;
}

/* 
Samples
=======
In
--
3 2 1 3 5 -1

Out
---
3 2 1 3 5 -1
*/

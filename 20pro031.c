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

typedef struct Node_ {
    int x;
    struct Node_* next;
} Node;

typedef struct {
    Node* head;
} List;

List create_empty_list() {
    List list;
    list.head = NULL;
    return list;
}

Node* new_node(int x) {
    Node* p;
    NEW(p, 1);
    p->x = x;
    p->next = NULL;
    return p;
}

void delete_node(Node* p) {
    free(p);
}

void erase_front(List* list_p) {
    Node* node_p = list_p->head;
    list_p->head = node_p->next;
    delete_node(node_p);
}

void clear_list(List* list_p) {
    while (list_p->head != NULL) {
        erase_front(list_p);
    }
}

void push_front(List* list_p, Node* node_p) {
    node_p->next = list_p->head;
    list_p->head = node_p;
}

#define FOREACH(list, node_p) for (Node* (node_p) = (list).head; (node_p) != NULL; (node_p) = (node_p)->next)

Node* search(List list, int q) {
    FOREACH(list, node_p) {
        if (node_p->x == q) {
            return node_p;
        }
    }
    return NULL;
}

void print_list(List list) {
    FOREACH(list, node_p) {
        printf("%d ", node_p->x);
    }
    printf("-1\n");
}

List read_list() {
    List list = create_empty_list();
    while (1) {
        int x;
        scanf("%d", &x);
        if (x == -1) break;
        Node* node_p = new_node(x);
        push_front(&list, node_p);
    }
    return list;
}

int main() {
    List list = read_list();
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
5 3 1 2 3 -1
*/

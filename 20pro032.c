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
    List l1 = read_list();
    List l2 = read_list();
    List common = create_empty_list();
    Node* np1 = l1.head;
    Node* np2 = l2.head;
    while (np1 != NULL && np2 != NULL) {
        if (np1->x == np2->x) {
            push_front(&common, new_node(np1->x));
            np1 = np1->next;
            np2 = np2->next;
        } else if (np1->x < np2->x) {
            np2 = np2->next;
        } else {
            np1 = np1->next;
        }
    }
    print_list(common);
    clear_list(&l1);
    clear_list(&l2);
    clear_list(&common);
    return 0;
}

/* 
Samples
=======
In
--
1 2 3 4 5 -1
2 4 6 7 -1
Out
---
2 4 -1
*/

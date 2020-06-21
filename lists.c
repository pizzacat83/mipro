#include <stdbool.h>
#include "./memory.h"
#include "./lists.h"
#include "./lists_element.h"

// ----- node -----
static ListSNode* node_new(ListSElement* const value_p) {
    ListSNode* np;
    NEW(np, 1);
    np->value = value_p;
    np->next = NULL;
    return np;
}

static void node_delete(ListSNode* const p) {
    lists_element_delete(p->value);
    free(p);
}

// ----- list -----

ListS lists_create_empty() {
    ListS list;
    list.head = NULL;
    list.tail = NULL;
    return list;
}

void lists_erase_front(ListS* const list_p) {
    ListSNode* node_p = list_p->head;
    list_p->head = node_p->next;
    if (list_p->head == NULL) {
        list_p->tail = NULL;
    }
    node_delete(node_p);
}

void lists_clear(ListS* const list_p) {
    while (list_p->head != NULL) {
        lists_erase_front(list_p);
    }
}

#define FOREACH(list, node_p) for (ListSNode* (node_p) = (list).head; (node_p) != NULL; (node_p) = (node_p)->next)

void lists_push_front(ListS* const list_p, ListSElement* const element_p) {
    ListSNode* node_p = node_new(element_p);
    if (list_p->head == NULL) {
        // tail == NULL
        list_p->head = node_p;
        list_p->tail = node_p;
    } else {
        node_p->next = list_p->head;
        list_p->head = node_p;
    }
}

void lists_push_back(ListS* const list_p, ListSElement* const element_p) {
    ListSNode* node_p = node_new(element_p);
    if (list_p->tail == NULL) {
        // head == NULL
        list_p->head = node_p;
        list_p->tail = node_p;
    } else {
        list_p->tail->next = node_p;
        list_p->tail = node_p;
    }
}

void lists_insert_after(ListS* const list_p, ListSNode* const parent_p, ListSElement* const element_p) {
    ListSNode* child_p = node_new(element_p);
    if (parent_p->next == NULL) {
        // update tail
        list_p->tail = child_p;
    }
    child_p->next = parent_p->next;
    parent_p->next = child_p;
}

void lists_print(ListS list, FILE* fp) {
    FOREACH(list, node_p) {
        lists_element_print(node_p->value, fp);
        fprintf(fp, " ");
    }
    fprintf(fp, "-1\n");
}

void lists_read(ListS* const list_p) {
    *list_p = lists_create_empty();
    while (1) {
        ListSElement* element_p = lists_element_new();
        bool ok = lists_element_read(element_p);
        if (!ok) {
            lists_element_delete(element_p);
            break;
        }
        lists_push_back(list_p, element_p);
    }
}

ListSNode* lists_search(ListS list, const ListSElement* const q_p) {
    FOREACH (list, node_p) {
        if (lists_element_is_equal(node_p->value, q_p)) {
            return node_p;
        }
    }
    return NULL;
}

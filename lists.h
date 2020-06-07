#ifndef H_LISTS
#define H_LISTS

#include <stdio.h>
#include "./lists_element.h"

typedef struct ListSNode_ {
    Element* value;
    struct ListSNode_* next;
} ListSNode;

typedef struct {
    ListSNode* head;
    ListSNode* tail;
} ListS;

ListS lists_create_empty(void);

void lists_erase_front(ListS* const list_p);

void lists_clear(ListS* const list_p);

#define LISTS_FOREACH(list, node_p) for (ListSNode* (node_p) = (list).head; (node_p) != NULL; (node_p) = (node_p)->next)

void lists_push_front(ListS* const list_p, Element* const element_p);

void lists_push_back(ListS* const list_p, Element* const element_p);

void lists_insert_after(ListS* const list_p, ListSNode* const parent_p, Element* const element_p);

void lists_print(ListS list, FILE* fp);

void lists_read(ListS* const list_p);

ListSNode* lists_search(ListS list, const Element* const q_p);

#endif

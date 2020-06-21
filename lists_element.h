#ifndef H_LISTS_ELEMENT
#define H_LISTS_ELEMENT

#include <stdbool.h>
#include <stdio.h>

typedef struct ListSElement ListSElement;

ListSElement* element_new(void);

void element_delete(ListSElement* const element_p);

void element_clone(const ListSElement* const src, ListSElement* const dst);

void element_print(const ListSElement* const element_p, FILE* const fp);

bool element_read(ListSElement* element_p);

bool element_is_equal(const ListSElement* const a, const ListSElement* const b);

#endif

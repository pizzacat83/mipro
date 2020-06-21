#ifndef H_LISTS_ELEMENT
#define H_LISTS_ELEMENT

#include <stdbool.h>
#include <stdio.h>

typedef struct ListSElement ListSElement;

ListSElement* lists_element_new(void);

void lists_element_delete(ListSElement* const element_p);

void lists_element_clone(const ListSElement* const src, ListSElement* const dst);

void lists_element_print(const ListSElement* const element_p, FILE* const fp);

bool lists_element_read(ListSElement* element_p);

bool lists_element_is_equal(const ListSElement* const a, const ListSElement* const b);

#endif

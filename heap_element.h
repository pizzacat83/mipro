#ifndef H_HEAP_ELEMENT
#define H_HEAP_ELEMENT

typedef struct Element Element;

void element_delete(Element* const ep);

typedef int (*CmpFunc)(const Element* const, const Element* const);

int element_cmp(const Element* const x, const Element* const y);

int element_revcmp(const Element* const x, const Element* const y);

#endif

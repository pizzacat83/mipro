#ifndef H_HEAP_ELEMENT
#define H_HEAP_ELEMENT

typedef struct HeapElement HeapElement;

void heap_element_delete(HeapElement* const ep);

typedef int (*CmpFunc)(const HeapElement* const, const HeapElement* const);

int cmp(const HeapElement* const x, const HeapElement* const y);

int revcmp(const HeapElement* const x, const HeapElement* const y);

#endif

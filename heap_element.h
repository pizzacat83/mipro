#ifndef H_HEAP_ELEMENT
#define H_HEAP_ELEMENT

typedef struct HeapElement HeapElement;

void heap_element_delete(HeapElement* const ep);

typedef int (*CmpFunc)(const HeapElement* const, const HeapElement* const);

int heap_element_cmp(const HeapElement* const x, const HeapElement* const y);

int heap_element_revcmp(const HeapElement* const x, const HeapElement* const y);

#endif

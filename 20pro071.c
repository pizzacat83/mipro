#include <stdio.h>
#include "./memory.h"
#include "./heap.h"
#include "./element_int.h"

int main() {
    size_t size;
    scanf("%ld", &size);
    Element** data;
    NEW(data, size);
    for (size_t i = 0; i < size; ++i) {
        Element* ep;
        NEW(ep, 1);
        scanf("%d", &ep->value);
        data[i] = ep;
    }
    Heap heap = HEAP.create_from(data, size, size, element_cmp);
    for (size_t i = 0; i < size; ++i) {
        printf("%d\n", HEAP.top(heap)->value);
        HEAP.pop(&heap);
    }
    HEAP.clear(&heap);
}

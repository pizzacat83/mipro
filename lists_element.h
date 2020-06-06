#include <stdbool.h>

typedef struct Element Element;

Element* element_new(void);

void element_delete(Element* const element_p);

void element_clone(const Element* const src, Element* const dst);

void element_print(const Element* const element_p, FILE* const fp);

bool element_read(Element* element_p);

bool element_is_equal(const Element* const a, const Element* const b);

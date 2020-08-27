#include <stddef.h>
#include <stdbool.h>
#include "set.h"

Set set_singleton(size_t i) {
    return 1lu<<i;
}

bool set_has(Set S, size_t i) {
    return (S & (1lu<<i)) != 0;
}

Set set_include(Set S, size_t i) {
    return S | (1lu<<i);
}

Set set_exclude(Set S, size_t i) {
    return S & ~(1lu<<i);
}

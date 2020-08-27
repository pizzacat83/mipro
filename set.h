#ifndef H_SET
#define H_SET

#include <stddef.h>
#include <stdbool.h>

typedef size_t Set;

Set set_singleton(size_t i);
bool set_has(Set S, size_t i);
Set set_include(Set S, size_t i);

Set set_exclude(Set S, size_t i);

#endif

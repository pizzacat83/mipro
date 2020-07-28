#ifndef H_BINTREE_VALUE_STRING
#define H_BINTREE_VALUE_STRING

#include "strings.h"
#include "bintree_value.h"

struct BinTreeValue {
    String str;
};

void bintree_value_delete(BinTreeValue* const value);

#endif

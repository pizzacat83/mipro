#include "strings.h"
#include "bintree_value.h"
#include "bintree_value_string.h"

void bintree_value_delete(BinTreeValue* const value) {
    string_delete(&value->str);
    free(value);
}

#include "strings.h"
#include "bintree_value.h"
#include "bintree_key_string.h"

void bintree_key_delete(BinTreeKey* const key) {
    string_delete(&key->str);
    free(key);
}

CmpResult bintree_cmp(const BinTreeKey* const str1, const BinTreeKey* const str2) {
    return string_cmp(str1->str, str2->str);
}

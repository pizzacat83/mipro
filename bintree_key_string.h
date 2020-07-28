#ifndef H_BINTREE_KEY_STRING
#define H_BINTREE_KEY_STRING

#include "strings.h"
#include "bintree_key.h"

struct BinTreeKey {
    String str;
};

void bintree_key_delete(BinTreeKey* const key);

CmpResult bintree_cmp(const BinTreeKey* const str1, const BinTreeKey* const str2);

#endif

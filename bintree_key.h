#ifndef H_BINTREE_KEY
#define H_BINTREE_KEY

#include "cmp.h"

typedef struct BinTreeKey BinTreeKey;

typedef CmpResult (*BinTreeKeyCmpFunc)(const BinTreeKey* const, const BinTreeKey* const);

void bintree_key_delete(BinTreeKey* const key);

#endif

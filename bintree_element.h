#ifndef H_BINTREE_ELEMENT
#define H_BINTREE_ELEMENT

#include "cmp.h"

typedef BinTreeKey;
typedef BinTreeValue;

typedef CmpResult (*BinTreeElementCmpFunc)(const BinTreeElement* const, const BinTreeElement* const);

void bintree_key_delete(BinTreeKey* const key);
void bintree_value_delete(BinTreeValue const value);

#endif

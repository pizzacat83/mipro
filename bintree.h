#ifndef H_BINTREE
#define H_BINTREE

#include "bintree_element.h"

typedef struct BinTreeNode_{
    struct BinTreeNode_* right;
    struct BinTreeNode_* left;
    struct BinTreeElement* parent;
    const BinTreeKey const * key;
    BinTreeValue* value;
} BinTreeNode;

typedef struct {
    BinTreeNode* root;
    BinTreeElementCmpFunc cmp;
} BinTree;

BinTree bintree_create(BinTreeElementCmpFunc cmp);

BinTreeNode* bintree_search(const BinTree* const tree, const BinTreeKey* const key);

// key, valueのメモリ確保は呼び出し側の責任
// key, valueのメモリ解放はBinTreeの責任
// keyがtreeに存在する場合，未定義
void bintree_insert(BinTree* const tree, const BinTreeKey* const key, BinTreeValue* const value);

#endif

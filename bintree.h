#ifndef H_BINTREE
#define H_BINTREE

#include <stdbool.h>
#include <stdio.h>
#include "bintree_key.h"
#include "bintree_value.h"

typedef struct BinTreeNode_{
    struct BinTreeNode_* right;
    struct BinTreeNode_* left;
    struct BinTreeNode_* parent;
    BinTreeKey* key;
    BinTreeValue* value;
} BinTreeNode;

typedef struct {
    BinTreeNode* root;
    BinTreeKeyCmpFunc cmp;
} BinTree;

BinTree bintree_create(BinTreeKeyCmpFunc cmp);

void bintree_clear(BinTree* const tree);

typedef bool (*ReadKeyValueFunc)(BinTreeKey** const key, BinTreeValue** const value);

BinTree bintree_read(
    BinTreeKeyCmpFunc cmp,
    // メモリ確保はread_key_valueの責任
    // メモリ解放はBinTreeの責任
    ReadKeyValueFunc read_key_value
);

typedef void (*PrintKeyValueFunc)(FILE* const out, const BinTreeKey* const key, const BinTreeValue* value);

void bintree_print_sorted(
    FILE* out,
    PrintKeyValueFunc print_key_value,
    const BinTree* const tree
);

BinTreeNode* bintree_search(const BinTree* const tree, const BinTreeKey* const key);

// key, valueのメモリ確保は呼び出し側の責任
// key, valueのメモリ解放はBinTreeの責任
// keyがtreeに存在する場合，未定義
void bintree_insert(BinTree* const tree, BinTreeKey* const key, BinTreeValue* const value);

#endif

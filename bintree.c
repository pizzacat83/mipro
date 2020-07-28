#pragma GCC diagnostic ignored "-Wmissing-prototypes"

#include <stddef.h>
#include <stdbool.h>
#include "memory.h"
#include "debug.h"
#include "bintree.h"

typedef BinTreeNode Node;
typedef BinTreeKey Key;
typedef BinTreeValue Value;

// key, valueのメモリ確保・解放は呼び出し側の責任
Node* node_new(Key* const key, Value* const value) {
    Node* node;
    NEW(node, 1);
    node->key = key;
    node->value = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void node_delete(Node* const node) {
    if (node == NULL) {
        return;
    }
    node_delete(node->left);
    node_delete(node->right);
    bintree_key_delete(node->key);
    bintree_value_delete(node->value);
    free(node);
}

BinTree bintree_create(BinTreeKeyCmpFunc cmp) {
    BinTree tree;
    tree.cmp = cmp;
    tree.root = NULL;
    return tree;
}

void bintree_clear(BinTree* const tree) {
    node_delete(tree->root);
}

// 要素の存在を返す
// keyがあればresにノードを格納
// keyがなければresに親となるべきノードを格納
bool search(const BinTree* const tree, const Key* const key, Node** const res) {
    Node* node = tree->root;
    Node* parent = NULL;
    while (node != NULL) {
        CmpResult c = tree->cmp(key, node->key);
        if (c == EQUAL) {
            *res = node;
            return true;
        }
        parent = node;
        if (c == LESS) {
            node = node->left;
        }
        if (c == GREAT) {
            node = node->right;
        }
    }
    *res = parent;
    return false;
}

Node* bintree_search(const BinTree* const tree, const Key* const key) {
    Node* res;
    if (search(tree, key, &res)) {
        return res;
    } else {
        return NULL;
    }
}

void bintree_insert(BinTree* const tree, Key* const key, Value* const value) {
    Node* node = node_new(key, value);
    if (tree->root == NULL) {
        tree->root = node;
        return;
    }
    Node* parent;
    bool found = search(tree, key, &parent); // false
    #ifdef DEBUG
    if (found) {
        log("duplicate key\n");
    }
    #endif
    node->parent = parent;
    if (tree->cmp(key, parent->key) == LESS) {
        #ifdef DEBUG
        if (parent->left != NULL) {
            log("insertion to non-null child\n");
        }
        #endif
        parent->left = node;
    } else {
        #ifdef DEBUG
        if (parent->right != NULL) {
            log("insertion to non-null child\n");
        }
        #endif
        parent->right = node;
    }
}

void print_node_sorted(
    FILE* out,
    PrintKeyValueFunc print_key_value,
    const Node* const node
) {
    if (node->left) {
        print_node_sorted(out, print_key_value, node->left);
    }
    print_key_value(out, node->key, node->value);
    if (node->right) {
        print_node_sorted(out, print_key_value, node->right);
    }
}

void bintree_print_sorted(
    FILE* out,
    PrintKeyValueFunc print_key_value,
    const BinTree* const tree
) {
    print_node_sorted(out, print_key_value, tree->root);
}

BinTree bintree_read(
    BinTreeKeyCmpFunc cmp,
    ReadKeyValueFunc read_key_value
) {
    BinTree tree = bintree_create(cmp);
    Key* key;
    Value* value;
    while (read_key_value(&key, &value)) {
        log("read ok\n");
        bintree_insert(&tree, key, value);
    }
    log("bintree EOF\n");
    return tree;
}

#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <stdio.h>
#include <stdbool.h>
#include "strings.h"
#include "bintree.h"
#include "bintree_key_string.h"
#include "bintree_value_string.h"
#include "debug.h"

bool string_split1(String src, String* const dst1, String* const dst2) {
    char* buf1;
    char* buf2;
    NEW(buf1, 1000+1);
    NEW(buf2, 1000+1);
    int res = sscanf(src.chars, "%1000s %1000s", buf1, buf2);
    if (res < 2) {
        return false;
    }
    *dst1 = string_from_chars(buf1);
    *dst2 = string_from_chars(buf2);
    free(buf1);
    free(buf2);
    return true;
}

bool read_key_value(BinTreeKey** const key, BinTreeValue** const value) {
    NEW(*key, 1);
    bool ok;
    string_try_read_new((*key)->str, 2000, ok);
    if (!ok) {
        log("main EOF\n");
        free(*key);
        return false;
    }
    NEW(*value, 1);
    string_try_read_new((*value)->str, 2000, ok);
    if (!ok) {
        log("main EOF\n");
        free(*value);
        return false;
    }
    return true;
}

void print_key_value(FILE* const out, const BinTreeKey* const key, const BinTreeValue* value) {
    string_print(out, key->str);
    printf(" ");
    string_print(out, value->str);
    printf("\n");
}


int main() {
    log("start read\n");
    BinTree tree = bintree_read(bintree_cmp, read_key_value);
    log("start print\n");
    bintree_print_sorted(stdout, print_key_value, &tree);
    bintree_clear(&tree);
    return 0;
}

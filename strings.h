#ifndef H_STRINGS
#define H_STRINGS

#include <stdio.h>
#include "memory.h"
#include "cmp.h"

typedef struct {
    char* chars;
    size_t length;
} String;

// NULL文字があるところまでコピーした新しい配列を作る
// charsの解放は呼び出し元の責任
String string_from_chars(const char* const chars);

#define string_read_new(str, length) do {\
    char* buf;\
    NEW(buf, (length) + 1);\
    scanf("%" #length "s", buf);\
    (str) = string_from_chars(buf);\
    free(buf);\
} while(0)

#define string_try_read_new(str, length, ok) do {\
    char* buf;\
    NEW(buf, (length) + 1);\
    int scanf_res = scanf("%" #length "s", buf);\
    if (scanf_res < 1) {\
        free(buf);\
        (ok) = false;\
    } else {\
        (str) = string_from_chars(buf);\
        free(buf);\
        (ok) = true;\
    }\
} while(0)

void string_delete(String* const str);

CmpResult string_cmp(String str1, String str2);

void string_print(FILE* const out, String str);

#endif

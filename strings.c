#include <stddef.h>
#include "strings.h"

static size_t chars_len(const char* const str) {
    const char* s = str;
    size_t l = 0;
    for (; *s != '\0'; ++s) {
        ++l;
    }
    return l;
}

static void copy_chars(const char* const src, char* const dst, size_t len_including_NULL) {
    for (size_t i = 0; i < len_including_NULL - 1; ++i) {
        dst[i] = src[i];
    }
    dst[len_including_NULL-1] = '\0';
}

void string_delete(String* const str) {
    free(str->chars);
    str->chars = NULL;
    str->length = 0;
}

CmpResult string_cmp(String str1, String str2) {
    for (size_t i = 0; ; ++i) {
        if (str1.chars[i] == '\0' && str2.chars[i] == '\0') {
            return EQUAL;
        }
        if (str1.chars[i] == '\0') {
            return LESS;
        }
        if (str2.chars[i] == '\0') {
            return GREAT;
        }
        CmpResult charcmp = cmp_builtin(str1.chars[i], str2.chars[i]);
        if (charcmp != EQUAL) {
            return charcmp;
        }
    }
    return EQUAL;
}

String string_from_chars(const char* const chars) {
    size_t len = chars_len(chars);
    char* s;
    NEW(s, len+1);
    copy_chars(chars, s, len+1);
    return (String){s, len};
}

void string_print(FILE* const out, String str){
    fprintf(out, "%s", str.chars);
}

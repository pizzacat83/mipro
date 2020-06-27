#include <stddef.h>
#include "strings.h"

static size_t chars_len(char* s) {
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

String helper_read_new_string(char* const buf) {
    size_t len = chars_len(buf);
    char* s;
    NEW(s, len + 1); // +1 for '\0'
    copy_chars(buf, s, len + 1);
    return (String){s, len};
}

void delete_string(String* const str) {
    free(str->chars);
    str->chars = NULL;
    str->length = 0;
}

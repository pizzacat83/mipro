#ifndef H_STRINGS
#define H_STRINGS

#include <stdio.h>
#include "memory.h"

typedef struct {
    char* chars;
    size_t length;
} String;

String helper_read_new_string(char* const buf);

#define read_new_string(str, length) do {\
    char* buf;\
    NEW(buf, (length) + 1);\
    scanf("%" #length "s", buf);\
    (str) = helper_read_new_string(buf);\
    free(buf);\
} while(0)

void delete_string(String* const str);

#endif

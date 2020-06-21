#ifndef H_MEMORY
#define H_MEMORY

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define NEW(p, n) do {\
    (p) = malloc((n) * sizeof(p[0]));\
    if ((p) == NULL) {\
        fprintf(stderr, "error in malloc (line #%d)\n", __LINE__);\
        exit(1);\
    }\
} while (0)

#define RENEW(p, n) do {\
    void* _tmp_pointer_for_renew = realloc((p), (n) * sizeof(p[0]));\
    if (_tmp_pointer_for_renew == NULL) {\
        fprintf(stderr, "error in realloc (line #%d)\n", __LINE__);\
        exit(1);\
    }\
    (p) = _tmp_pointer_for_renew;\
} while (0)

#endif

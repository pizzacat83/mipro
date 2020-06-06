#ifndef H_MEMORY
#define H_MEMORY

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define NEW(p, n) {\
    (p) = malloc((n) * sizeof(p[0]));\
    if ((p) == NULL) {\
        fprintf(stderr, "error in malloc (line #%d)\n", __LINE__);\
        exit(1);\
    }\
}

#endif

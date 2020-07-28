#ifndef H_DEBUG
#define H_DEBUG

#include <stdio.h>

#ifdef DEBUG
#define log(s, ...) fprintf(stderr, s, ##__VA_ARGS__)
#else
#define log
#endif

#endif

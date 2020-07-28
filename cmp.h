#ifndef H_CMP
#define H_CMP

typedef enum {
    LESS = -1,
    EQUAL = 0,
    GREAT = 1,
} CmpResult;

#define cmp_builtin(x, y) (\
    (x) == (y) ? EQUAL \
  : (x) > (y) ? GREAT \
  : LESS \
)

#endif

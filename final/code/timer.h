// ----- timer -----
#include <sys/time.h>
#include <time.h>

#ifdef TIMER
struct timeval t_start;
struct timeval t_stop;

#define tic() do {\
    gettimeofday(&t_start, NULL); \
} while (0)

#define toc(n) do {\
    gettimeofday(&t_stop, NULL);\
    fprintf(stderr, "%d: %lf ms\n", n, difftime(t_stop.tv_sec, t_start.tv_sec) * 1000 + (double)((t_stop.tv_usec) - t_start.tv_usec)/1000);\
} while (0)
#else
#define tic()
#define toc(n)
#endif

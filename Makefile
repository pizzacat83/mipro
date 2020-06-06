CC = gcc
CFLAGS = -g -fsanitize=undefined -Werror -Wall -Wextra -Wconversion -Wbad-function-cast -Wcast-align -Wcast-qual -Wdisabled-optimization -Wdouble-promotion -Wfloat-equal -Wformat -Winit-self -Wjump-misses-init -Wlogical-op -Wmissing-include-dirs -Wmissing-prototypes -Wmultichar -Wpointer-arith -Wswitch-default -Wswitch-enum -Wundef -Wunsafe-loop-optimizations -Wwrite-strings

SOURCES = $(wildcard *.c)
DEPENDS = $(patsubst %.c,%.d,$(SOURCES))

%.d: %.c
	$(CC) $< -MF $@ -MM $(CFLAGS)

-include $(DEPENDS)

20pro081.out: 20pro081.o lists.o graph_lists.o graph_lists_element.o
	$(CC) -o $@ $^ $(CFLAGS) 

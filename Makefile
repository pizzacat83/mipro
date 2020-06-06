CC = gcc
CFLAGS = -g -fsanitize=undefined -Werror -Wall -Wextra -Wconversion -Wbad-function-cast -Wcast-align -Wcast-qual -Wdisabled-optimization -Wdouble-promotion -Wfloat-equal -Wformat -Winit-self -Wjump-misses-init -Wlogical-op -Wmissing-include-dirs -Wmissing-prototypes -Wmultichar -Wpointer-arith -Wswitch-default -Wswitch-enum -Wundef -Wunsafe-loop-optimizations -Wwrite-strings

SOURCES = $(wildcard *.c)
AUTO_DEPENDS = $(patsubst %.c,%.o.d,$(SOURCES))
MANUAL_DEPENDS = $(patsubst %.c,%.d,$(SOURCES))

%.o.d: %.c
	$(CC) -MF $@ $< -MM $(CFLAGS)

%.out:
	$(CC) -o $@ $^ $(CFLAGS)
 
-include $(AUTO_DEPENDS)

-include $(MANUAL_DEPENDS)

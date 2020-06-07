CC = gcc
CFLAGS = -g -fsanitize=undefined -Werror -Wall -Wextra -Wconversion -Wbad-function-cast -Wcast-align -Wcast-qual -Wdisabled-optimization -Wdouble-promotion -Wfloat-equal -Wformat -Winit-self -Wjump-misses-init -Wlogical-op -Wmissing-include-dirs -Wmissing-prototypes -Wmultichar -Wpointer-arith -Wswitch-default -Wswitch-enum -Wundef -Wunsafe-loop-optimizations -Wwrite-strings

SOURCES = $(wildcard *.c)
C_DEPENDS = $(patsubst %.c,%.c.d,$(SOURCES))
O_DEPENDS = $(patsubst %.c,%.o.d,$(SOURCES))

# .c をコンパイルするときの依存関係ファイル
%.c.d: %.c
	$(CC) -MF $@ $< -MM $(CFLAGS)

%.o.d: %.c.d
	sed -e 's/^.*:\s*//' -e 's/\\\s*$$//g' < $<| \
	tr '\n' ' ' | \
	sed -e 's/^\s*//g' -e 's/\s*$$//g' -e 's/\s\s*/ /g' -e 's/\.[ch]/.c/g'| \
	xargs --delimiter=" " -I \{\} bash -c "[ -e '{}' ] && echo {} || true" | \
	sed -e 's/\.c/\.o/' | \
	tr '\n' ' ' | \
	sed -e 's/^/$(patsubst %.o.d,%.out,$@): /' -e 's/$$/\n/' > $@

%.out:
	bash run_tests.sh
	$(CC) -o $@ $^ $(CFLAGS)
 
-include $(C_DEPENDS)

-include $(O_DEPENDS)

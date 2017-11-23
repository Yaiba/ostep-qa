.PHONY : clean

objects := $(patsubst %.c, %.o, $(wildcard *.c))
all: $(objects)

$(objects): %.o: %.c
	@gcc $(CFLAGS) $< -o $@
	@chmod +x $@

clean:
	@rm -rf *.o

#
# Makefile
# alex, 2016-11-29 16:48
#

TARGET=elf_parser
CC=gcc
CFLAGS=-g
C_SRC=$(shell find . -name "*.c")
C_OBJ=$(C_SRC:%.c=%.o)
#C_OBJ=$(patsubst %.c, %.o, $(C_SRC))
HEADERS=$(shell find . -name "*.h")

.PHONY: clean run

$(TARGET): $(C_OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(C_OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

# vim:ft=make
#

CC = gcc
AS = as
BIN = bin

CFLAGS = -Wall -g -std=c99 -fPIC -ffreestanding -D_PWRNX_SOURCE

OBJECTS += $(BIN)/syscall.o
OBJECTS += $(BIN)/malloc.o
OBJECTS += $(BIN)/stdlib.o
OBJECTS += $(BIN)/conversion.o
OBJECTS += $(BIN)/setjmp.o
OBJECTS += $(BIN)/ctype.o
OBJECTS += $(BIN)/stream.o
OBJECTS += $(BIN)/printf.o
OBJECTS += $(BIN)/string.o

all: $(BIN) $(OBJECTS)
	ar rcs $(BIN)/pwrnxlibc.a $(OBJECTS)

clean:
	if [ -d $(BIN) ]; then rm -r $(BIN); fi

$(BIN):
	mkdir $(BIN)

$(BIN)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: src/%.s
	$(AS) $(ASFLAGS) $< -o $@

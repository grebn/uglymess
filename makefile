# Makefile

# Compiler
CC = gcc

# Flags
CFLAGS  = -g -fstack-check -std=c89
LDFLAGS =
LFLAGS =
# Objects
OBJ = main.o

# Source files
SRC = main.c

# Output executable
BIN = main

all: build clean
	@echo $(BIN) has been compiled

build: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN) $(OBJ) $(LFLAGS) $(LDFLAGS)

clean:
	rm -f *.o
	rm -f clayer/*.o
	@echo clean up finished

rebuild: clean build clean

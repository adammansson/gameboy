# A simple Makefile

# set the compiler
CC := cc

# set the compiler flags
CFLAGS := -Wall -Wextra -std=c2x -pedantic

SRCS = $(wildcard src/*/*.c src/*.c *.c )
HDRS = $(wildcard src/*/.h src/*.h *.h)

# generate names of object files
OBJS = ${SRCS:.c=.o}

# name of executable
EXEC := gameboy

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# default recipe
all: $(EXEC)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean


# Makefile
# Modified from chatgpt

CC = gcc
CFLAGS = -Wall -O2

# Default choice (can be overridden on the command line)
CHOICE ?= mylib1

# Source/object files
OBJS = strmain.o $(CHOICE).o

# Target executable
TARGET = strmain

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) -c $(OPTS) $<

clean:
	rm -f *.o $(TARGET)






















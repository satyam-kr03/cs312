# all source files
SRCS = hw.c echo.c echo2.c

# compiler options
CC = gcc
CFLAGS = -Wall -O
LIBS = -lm

all: hw echo echo2 printlog

hw: hw.c
	$(CC) $(CFLAGS) -o hw hw.c

echo: echo.c
	$(CC) $(CFLAGS) -o echo echo.c

echo2: echo2.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f hw echo echo2

printlog: printlog.c
	$(CC) $(CFLAGS) -o printlog printlog.c $(LIBS)
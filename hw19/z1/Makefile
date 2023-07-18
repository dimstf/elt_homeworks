.PHONY: all clean

CC=gcc
SRC=src/main.c
EXEC=bin/main
CFLAGS=-o
RMCMD=rm -f

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(EXEC)
	
clean:
	$(RMCMD) $(EXEC)

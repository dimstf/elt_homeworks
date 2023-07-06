.PHONY: all clean

CC=gcc
SRC1=src/main.c
SRC2=src/interface.c
EXEC=bin/main
CFLAGS=-lncurses -o
RMCMD=rm -f

all: $(EXEC)

$(EXEC): $(SRC1) $(SRC2)
	$(CC) $(SRC1) $(SRC2) $(CFLAGS) $(EXEC)
	
clean:
	$(RMCMD) $(EXEC)

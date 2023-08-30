.PHONY: all clean

CC=gcc
SRC1=src/cli.c
SRC2=src/echoserv.c
EXEC1=bin/cli
EXEC2=bin/echoserv
CFLAGS=-o
RMCMD=rm -f

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(SRC1)
	$(CC) $(SRC1) $(CFLAGS) $(EXEC1)

$(EXEC2): $(SRC2)
	$(CC) $(SRC2) $(CFLAGS) $(EXEC2)
	
clean:
	$(RMCMD) $(EXEC1) $(EXEC2)

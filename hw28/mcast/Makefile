.PHONY: all clean

CC=gcc
SRC1=src/sender.c
SRC2=src/recv.c
EXEC1=bin/sender
EXEC2=bin/recv
CFLAGS=-o
RMCMD=rm -f

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(SRC1)
	$(CC) $(SRC1) $(CFLAGS) $(EXEC1)
$(EXEC2): $(SRC2)
	$(CC) $(SRC2) $(CFLAGS) $(EXEC2)
	
clean:
	$(RMCMD) $(EXEC1) $(EXEC2)

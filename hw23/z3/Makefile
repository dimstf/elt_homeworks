.PHONY: all clean

CC=gcc
SERV_SRC=src/serv.c
CLI_SRC=src/cli.c
QUE_SRC=src/queue.c
SERV_EXEC=bin/serv
CLI_EXEC=bin/cli
CFLAGS=-lpthread -o
RMCMD=rm -f

all: $(SERV_EXEC) $(CLI_EXEC)

$(SERV_EXEC): $(SERV_SRC) $(QUE_SRC)
	$(CC) $(SERV_SRC) $(QUE_SRC) $(CFLAGS) $(SERV_EXEC)

$(CLI_EXEC): $(CLI_SRC)
	$(CC) $(CLI_SRC) $(CFLAGS) $(CLI_EXEC)

clean:
	$(RMCMD) $(SERV_EXEC) $(CLI_EXEC)

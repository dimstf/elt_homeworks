.PHONY: all clean

CC=gcc
SERV_SRC=src/serv.c
CLI_SRC=src/cli2.c
SERV_EXEC=bin/serv
CLI_EXEC=bin/cli2
CFLAGS=-o
RMCMD=rm -f

all: $(SERV_EXEC) $(CLI_EXEC)

$(SERV_EXEC): $(SERV_SRC)
	$(CC) $(SERV_SRC) $(CFLAGS) $(SERV_EXEC)

$(CLI_EXEC): $(CLI_SRC)
	$(CC) $(CLI_SRC) $(CFLAGS) $(CLI_EXEC)

clean:
	$(RMCMD) $(SERV_EXEC) $(CLI_EXEC)

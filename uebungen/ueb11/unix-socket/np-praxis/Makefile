CC = gcc
CFLAGS = -Wall

BINARIES = test-cli iter-srv thread-srv prethread-srv fork-srv prefork-srv

TEST_CLI_OBJS = test-cli.o tcp-connect.o readwrite.o barrier.o
SRV_OBJS = daemon-init.o tcp-listen.o readwrite.o handle-client.o srv-stats.o
ITER_SRV_OBJS = iter-srv.o $(SRV_OBJS)
THREAD_SRV_OBJS = thread-srv.o $(SRV_OBJS)
PRETHREAD_SRV_OBJS = prethread-srv.o $(SRV_OBJS)
FORK_SRV_OBJS = fork-srv.o $(SRV_OBJS)
PREFORK_SRV_OBJS = prefork-srv.o $(SRV_OBJS)

all: $(BINARIES)

test-cli: $(TEST_CLI_OBJS)
	$(CC) -o $@ $(TEST_CLI_OBJS) -lpthread

iter-srv: $(ITER_SRV_OBJS)
	$(CC) -o $@ $(ITER_SRV_OBJS) -lm

thread-srv: $(THREAD_SRV_OBJS)
	$(CC) -o $@ $(THREAD_SRV_OBJS) -lm -lpthread

prethread-srv: $(PRETHREAD_SRV_OBJS)
	$(CC) -o $@ $(PRETHREAD_SRV_OBJS) -lm -lpthread

fork-srv: $(FORK_SRV_OBJS)
	$(CC) -o $@ $(FORK_SRV_OBJS) -lm

prefork-srv: $(PREFORK_SRV_OBJS)
	$(CC) -o $@ $(PREFORK_SRV_OBJS) -lm

clean:
	rm -f $(BINARIES) *.o

.c.o:
	$(CC) -c $(CFLAGS) $*.c

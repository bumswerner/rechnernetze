CC = gcc
CFLAGS = -Wall

BINARIES = cat1 cat2 daemon exec-test exit-test fork-ids logfile overflow \
  quiz1 quiz2 read-data-stdin read-data readn-data-stdin show-ids \
  signal-block signal-wait syslog wait-child write-data

all: $(BINARIES)

cat1: cat1.o
	$(CC) -o $@ $@.o

cat2: cat2.o
	$(CC) -o $@ $@.o

daemon: daemon.o
	$(CC) -o $@ $@.o

exec-test: exec-test.o
	$(CC) -o $@ $@.o

exit-test: exit-test.o
	$(CC) -o $@ $@.o

fork-ids: fork-ids.o
	$(CC) -o $@ $@.o

logfile: logfile.o
	$(CC) -o $@ $@.o

overflow: overflow.o
	$(CC) -o $@ $@.o

quiz1: quiz1.o
	$(CC) -o $@ $@.o

quiz2: quiz2.o
	$(CC) -o $@ $@.o

read-data-stdin: read-data-stdin.o
	$(CC) -o $@ $@.o

read-data: read-data.o
	$(CC) -o $@ $@.o

readn-data-stdin: readn-data-stdin.o readn.o writen.o
	$(CC) -o $@ $@.o readn.o writen.o

show-ids: show-ids.o
	$(CC) -o $@ $@.o

signal-block: signal-block.o
	$(CC) -o $@ $@.o

signal-wait: signal-wait.o
	$(CC) -o $@ $@.o

syslog: syslog.o
	$(CC) -o $@ $@.o

wait-child: wait-child.o
	$(CC) -o $@ $@.o

write-data: write-data.o
	$(CC) -o $@ $@.o

clean:
	rm -f $(BINARIES) *.o

.c.o:
	$(CC) -c $(CFLAGS) $*.c

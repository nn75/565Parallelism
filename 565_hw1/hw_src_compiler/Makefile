CC=gcc
CFLAGS=-O3 -std=c99

all: loop_performance

%: %.c
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -f loop_performance *~

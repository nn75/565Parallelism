CC=gcc
CFLAGS=-O0 -std=c99

all: loop_performance loop_fusion loop_reverse loop_unroll

%: %.c
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -f loop_performance loop_fusion loop_reverse loop_unroll *~

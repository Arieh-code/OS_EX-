CC = gcc
CFLAGS = -Wall -Werror -fPIC
LDFLAGS = -shared

all: cmp copy codecA codecB encode decode shell

tool1: cmp.c
	$(CC) $(CFLAGS) -o cmp cmp.c

tool2: copy.c
	$(CC) $(CFLAGS) -o copy copy.c

codecA: codecA.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o libcodecA.so codecA.c

codecB: codecB.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o libcodecB.so codecB.c

encode: encode.c
	$(CC) $(CFLAGS) -o encode encode.c

decode: decode.c
	$(CC) $(CFLAGS) -o decode decode.c

shell: stshell.c 
	$(CC) $(CFLAGS) -o shell stshell.c 

clean:
	rm -f cmp copy libcodecA.so libcodecB.so encode decode shell

.PHONY: all clean

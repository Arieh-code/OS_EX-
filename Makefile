CC = gcc
CFLAGS = -Wall -Werror -fPIC
LDFLAGS = -shared

all: cmp copy codecA codecB encode decode shell

cmp: cmp.c
	$(CC) $(CFLAGS) -o cmp cmp.c

copy: copy.c
	$(CC) $(CFLAGS) -o copy copy.c

codecA: codecA.c codecA.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o libcodecA.so codecA.c

codecB: codecB.c codecB.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o libcodecB.so codecB.c

encode: encode.c
	$(CC) $(CFLAGS) -o encode encode.c -ldl

decode: decode.c codecA.h codecB.h
	$(CC) $(CFLAGS) -o decode decode.c -ldl

shell: stshell.c 
	$(CC) $(CFLAGS) -o shell stshell.c 

clean:
	rm -f cmp copy libcodecA.so libcodecB.so encode decode shell

.PHONY: all clean




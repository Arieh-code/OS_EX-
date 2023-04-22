CC = gcc
CFLAGS = -Wall -Werror -fPIC
LDFLAGS = -shared

all: tool1 tool2 codecA codecB encode decode

tool1: tool1.c
	$(CC) $(CFLAGS) -o tool1 tool1.c

tool2: tool2.c
	$(CC) $(CFLAGS) -o tool2 tool2.c

codecA: codecA.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o libcodecA.so codecA.c

codecB: codecB.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o libcodecB.so codecB.c

encode: encode.c
	$(CC) $(CFLAGS) -o encode encode.c

decode: decode.c
	$(CC) $(CFLAGS) -o decode decode.c

clean:
	rm -f tool1 tool2 libcodecA.so libcodecB.so encode decode

.PHONY: all clean

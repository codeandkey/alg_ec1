CC = gcc
CFLAGS = -O3 -std=gnu99
LDFLAGS =

all: sort_selection sort_bubble

sort_selection: sort_selection.c
	$(CC) $(CFLAGS) sort_selection.c -o sort_selection $(LDFLAGS)

sort_bubble: sort_bubble.c
	$(CC) $(CFLAGS) sort_bubble.c -o sort_bubble $(LDFLAGS)

clean:
	rm sort_bubble sort_selection

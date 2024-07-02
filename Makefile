CC = gcc
CFLAGS = -Wall -Wextra -std=c99

EXEC1 = mounter

.PHONY: all clean

all: $(EXEC1)

$(EXEC1): main.c
	$(CC) $(CFLAGS) main.c -o $(EXEC1)

clean:
	rm -f $(EXEC1) $(EXEC2)

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

EXEC1 = mounter
EXEC2 = mounter2

.PHONY: all clean

all: $(EXEC1) $(EXEC2)

$(EXEC1): main.c
	$(CC) $(CFLAGS) main.c -o $(EXEC1)

$(EXEC2): main2.c
	$(CC) $(CFLAGS) main2.c -o $(EXEC2)

clean:
	rm -f $(EXEC1) $(EXEC2)
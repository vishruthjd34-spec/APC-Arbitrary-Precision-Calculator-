CC     = gcc
CFLAGS = -Wall
TARGET = a.out
SRCS   = main.c apc.c add.c sub.c mul.c div.c

$(TARGET): $(SRCS) apc.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.o

.PHONY: clean

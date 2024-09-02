CC=gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lncurses

TARGET = shell

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(LIBS)

.PHONY: clean

clean:
	rm -f $(TARGET)


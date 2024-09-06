CC=gcc
CFLAGS = -Wall -Wextra -Wformat-extra-args -std=c99
LIBS = -lncurses

TARGET = shell

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(LIBS)

.PHONY: clean

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)


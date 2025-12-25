CC = gcc
CFLAGS = -Wall
TARGET = sed_simplified
SOURCES = main.c sed.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: all clean

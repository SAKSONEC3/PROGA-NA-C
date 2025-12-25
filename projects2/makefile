CC = gcc
CFLAGS = -Wall
PROG = test
SRC = main.c sed.c

all: $(PROG)

$(PROG): $(SRC)
	$(CC) $(CFLAGS) -o $(PROG) $(SRC)

clean:
	rm -f $(PROG) file.txt test*.txt

run:
	@echo "test 1" > test1.txt
	@echo "test 2" >> test1.txt
	@./$(PROG) test1.txt 's/test/TEST/'
	@cat test1.txt

clear: clean

.PHONY: all clean run clear

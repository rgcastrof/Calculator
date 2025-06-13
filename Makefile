NAME = calc

CC = gcc
CFLAGS = -Wall -Wextra -pedantic

SRC = calc.c util.c
OBJ = calc.o util.o

BIN_DIR = /usr/local/bin

BIN = $(BIN_DIR)/$(NAME)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lm

calc.o: calc.c util.h
	$(CC) $(CFLAGS) -c calc.c -o calc.o

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c -o util.o

install: all
	@mkdir -p $(BIN_DIR)
	@cp $(NAME) $(BIN_DIR)

uninstall:
	rm -f $(BIN)

clean:
	rm -f $(OBJ) $(NAME)

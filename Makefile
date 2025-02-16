NAME = calc

CC = gcc
CFLAGS = -Wall -Wextra -pedantic

SRC = calc.c
OBJ = calc.o

BIN_DIR = /usr/local/bin

BIN = $(BIN_DIR)/$(NAME)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lm

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

install: all
	@mkdir -p $(BIN_DIR)
	@cp $(NAME) $(BIN_DIR)

uninstall:
	rm -f $(BIN)

clean:
	rm -f $(OBJ) $(NAME)

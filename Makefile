
CC=gcc
C_FLAGS=-std=c99 -Wall -pedantic
LD_FLAGS=$(C_FLAGS)
SRC=nqueen.c
OBJ=$(SRC:.c=.o)
BIN=$(SRC:.c=)

all: $(OBJ)
	$(CC) $(LD_FLAGS) -o $(BIN) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BIN)

.PHONY: all clean

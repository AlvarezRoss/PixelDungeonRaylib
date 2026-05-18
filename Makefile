CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = src/main.c src/helper.c src/map.c
OBJ = $(SRC:.c=.o)

TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
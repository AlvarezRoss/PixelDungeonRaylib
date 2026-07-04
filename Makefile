CC = gcc
CFLAGS = -Wall -std=c99 -MMD -MP
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = src/main.c src/helper.c src/map.c src/enemyBehaviours.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)

-include $(DEP)
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -MMD -MP

SRC = src/main.c src/helper.c src/map.c src/enemyBehaviours.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

TARGET = game

ifeq ($(OS),Windows_NT)
	LDFLAGS = -static
	LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
	TARGET := game.exe
else
	LDFLAGS =
	LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)

-include $(DEP)
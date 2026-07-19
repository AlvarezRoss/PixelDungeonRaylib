CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -MMD -MP

SRC = src/main.c src/helper.c src/map.c src/enemyBehaviours.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

TARGET = game

ifeq ($(OS),Windows_NT)

	TARGET := game.exe 
	RAYLIB_PATH ?= C:/raylib/raylib
	CFLAGS += -I$(RAYLIB_PATH)/src
	LDFLAGS += -L$(RAYLIB_PATH)/src
	LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

	RM = cmd /C del /Q
	
else
	LDFLAGS =
	LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	RM = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	powershell -Command "Remove-Item -Force -ErrorAction SilentlyContinue src\*.o,src\*.d,$(TARGET)"
else
	rm -f $(OBJ) $(DEP) $(TARGET)
endif

-include $(DEP)
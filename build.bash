#!/bin/bash
mkdir -p build

gcc src/main.c src/helper.c src/enemyBheaviours.c src/helper.c src/map.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
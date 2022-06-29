SOURCE_FILES = src/main.c
PROJ_NAME = game
CFLAGS = -std=c99
INC_DIRS = -Iinclude
LIB_DIRS = -Llib
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
all: 
	gcc -Wall $(SOURCE_FILES)  -o $(PROJ_NAME) $(INC_DIRS) $(LIB_DIRS) $(CFLAGS) $(LDFLAGS)

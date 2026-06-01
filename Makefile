CC = D:/mingw64/bin/gcc

RAYLIB_PATH = D:/raylib-5.5_win64_mingw-w64

CFLAGS = -Wall -std=c99 -I$(RAYLIB_PATH)/include
LDFLAGS = -L$(RAYLIB_PATH)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

OUT = tetris.exe

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del *.o tetris.exe
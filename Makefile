CC = clang
IDIR = -I/opt/homebrew/include -I/Users/samuelreid/Desktop/programming/include
LDIR = -L/opt/homebrew/lib
CFLAGS = -Wall -Wpedantic -Wextra -Werror -Wno-unused-parameter -std=c99

all: glad window
	$(CC) $(IDIR) $(LDIR) $(CFLAGS) -lglfw .glad.o .window.o main.c program.c matrix.c shaders.c camera.c models.c -o game

glad:
	$(CC) $(IDIR) -Wall -Wextra -Werror -std=c99 -c glad.c -o .glad.o

window:
	$(CC) $(IDIR) $(CFLAGS) -c window.c -o .window.o
  
clean:
	rm game .window.o .glad.o

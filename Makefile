NAME=triangles
CC=gcc
CFLAGS=I
# This appears to be the absolute minimum to compile properly
INCLUDE=-I/opt/vc/include \
	`pkg-config --cflags sdl`
# Also the minimum
LDFLAGS=-L/opt/vc/lib -lGLESv2 -lEGL `pkg-config --libs sdl`

main: src/main.c
	$(CC) -o $(NAME) src/main.c $(INCLUDE) $(LDFLAGS)

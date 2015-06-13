NAME=triangles
CC=gcc
CFLAGS=I
# This appears to be the absolute minimum to compile properly
INCLUDE=-I/opt/vc/include \
	`pkg-config --cflags sdl2`
# Also the minimum
LDFLAGS=-L/opt/vc/lib -lGLESv2 -lEGL `pkg-config --libs sdl2`

main: main.c
	$(CC) -o $(NAME) main.c $(INCLUDE) $(LDFLAGS)

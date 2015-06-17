NAME=triangles
CC=gcc
CFLAGS=I
# This appears to be the absolute minimum to compile properly
INCLUDE=-I/opt/vc/include \
	-I/opt/vc/include/interface/vcos/pthreads \
	-I/opt/vc/include/interface/vmcs_host/linux
# Also the minimum
LDFLAGS=-L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host

main: main.c
	$(CC) -o $(NAME) shaderstuff.c initogl.c main.c $(INCLUDE) $(LDFLAGS)

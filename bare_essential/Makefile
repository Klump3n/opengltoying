NAME=triangles
CC=gcc
CFLAGS=I
# This appears to be the absolute minimum to compile properly
INCLUDE=-I/opt/vc/include \
	-I/opt/vc/include/interface/vcos/pthreads \
	-I/opt/vc/include/interface/vmcs_host/linux \
	-I/usr/include/arm-linux-gnueabihf/c++/4.8 \
	-I/usr/include/c++/4.8.2 \
	-I/home/pi/coding/glm/glm
# Also the minimum
LDFLAGS=-L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host

main: main.c
	$(CC) -o $(NAME) shaderstuff.c initogl.c main.c $(INCLUDE) $(LDFLAGS)

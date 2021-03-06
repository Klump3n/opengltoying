NAME=triangles
CC=g++
CFLAGS=I
# This appears to be the absolute minimum to compile properly
INCLUDE=-I/opt/vc/include \
	-I/opt/vc/include/interface/vcos/pthreads \
	-I/opt/vc/include/interface/vmcs_host/linux \
	-I/home/pi/coding/glm/glm
# Also the minimum
LDFLAGS=-L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host

main: main.cpp
	$(CC) shaderstuff.c initogl.c main.cpp -o $(NAME) $(INCLUDE) $(LDFLAGS)

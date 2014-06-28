#comment: written for mingw + msys
#compiler: GNU C / binutils
CC = gcc
all:
	$(CC)socket.c -o socket.exe -lws2_32
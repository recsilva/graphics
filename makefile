CFLAGS = -Wall
LIBS = -lglfw
CC = g++

CPPFILES = src/*.cpp glad/glad.c


all:
	$(CC) $(CFLAGS) $(CPPFILES) -o program $(LIBS)
	./program
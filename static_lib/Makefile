CC= 	arm-linux-gnueabi-gcc
CFLAGS= -g -Wall -std=c99
TARGET=	main

$(TARGET): main.o libmytest.a
	${CC} -static -o $@ $^

# create an intermediary object file instead of an executable with the -c flag
main.o: main.c
	${CC} -c $< -o $@
libtest.o: libtest.c libtest.h
	${CC} -c -o $@ $<

# create the actual library. Pay attention to start its name with lib and add 
# the .a extension for static libraries
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ar creates and maintains library archives
# r: insert with replacement
# c: create new archive
# s: write an index
libmytest.a: libtest.o
	ar rcs $@ $^

# additional information
# $@ : target
# $^ : all prerequisites
# $< : just the first prerequisite
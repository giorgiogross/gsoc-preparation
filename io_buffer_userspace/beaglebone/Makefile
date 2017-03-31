CC= 	arm-linux-gnueabi-gcc
CFLAGS= -g -W -std=c99
TARGET=	uart_tester
SRC=	uart_tester.c connector.c filelog.c
OBJ=	$(SRC:.c=.o)

uart_tester: $(OBJ)
	${CC} -static -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

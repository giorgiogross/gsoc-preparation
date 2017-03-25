CC= 	arm-linux-gnueabi-gcc
TARGET=	uart_tester
SRC=	uart_tester.c
OBJ=	$(SRC:.c=.o)

uart_tester: $(OBJ)
	${CC} -static -o $@ $(OBJ)

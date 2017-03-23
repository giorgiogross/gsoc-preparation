/*
This program will read input data received on UART1
on the BeagleBone and count how many packages are
received. The message counter will be compared with
the expected message count NUM_MSGS. On UART1 there
is an Arduino connected which will send NUM_MSGS.
*/
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define NUM_MSGS 200

int main(){
    printf("Starting uart tester");

    int fd ;
    fd = open("/dev/ttyO1",O_RDWR | O_NOCTTY);
    if(fd) exit(-1);

    close(fd);
}
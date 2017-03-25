/*
This program will read input data received on UART1
on the BeagleBone and count how many packages are
received. The message counter will be compared with
the expected message count NUM_MSGS. On UART1 there
is an Arduino connected which will send NUM_MSGS.
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define NUM_MSGS 200

int main(){
    printf("Starting uart tester\n");

    int fd_ttyO1 = open("/dev/ttyO1",O_RDWR | O_NOCTTY);
    if(fd_ttyO1 == -1) printf("Error opening ttyO1\n");
    else printf("Opened ttyO1\n");

    struct termios config;
    // get current settings of serial port
    tcgetattr(fd_ttyO1, &config);
    // adjust baud rate
    cfsetispeed(&config, B115200);
    cfsetospeed(&config, B115200);

    // adjust bit settings
    // no parity
    config.c_cflag &= ~PARENB;
    // cleat data bit size
    config.c_cflag &= ~CSIZE;
    // 8 data bit
    config.c_cflag |= CS8; 
    // one stop bit
    config.c_cflag &= ~CSTOPB;

    // apply the settings
    tcsetattr(fd_ttyO1, TCSANOW, &config);

    close(fd_ttyO1);
}
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
#include <signal.h>

#define NUM_MSGS 200

int fd_ttyO1 = -1;

void quitHandler(int s) {
    if(fd_ttyO1 != -1) close(fd_ttyO1);
    printf("Quit\n"); // maybe add some stats later.
    exit(1);
}

int main(){
    // register signal handler to quit the program
    struct sigaction sigHandler;
    sigHandler.sa_handler = quitHandler;
    sigHandler.sa_flags = 0;
    sigemptyset(&sigHandler.sa_mask);
    sigaction(SIGINT, &sigHandler, NULL);

    printf("Starting uart tester\n");
    fd_ttyO1 = open("/dev/ttyO1",O_RDWR | O_NOCTTY);
    if(fd_ttyO1 == -1) {
        printf("Error opening ttyO1\n");
        return -1;
    } else printf("Opened ttyO1\n");

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

    // reading data
    config.c_cflag |= CREAD | CLOCAL;
    config.c_cc[VMIN] = 255; // if we receive more than 255 bytes we might lose some
    config.c_cc[VTIME] = 0;

    // apply the settings
    tcsetattr(fd_ttyO1, TCSANOW, &config);

    // 10 byte buffer
    char buffer[200];
    ssize_t counter = 0;
    // exit with ctrl+c
    for(;;) {
        ssize_t readAmnt = read(fd_ttyO1, buffer, sizeof(buffer));
        counter += readAmnt;
        printf("Read %d bytes: %s           #total until now: %d\n", readAmnt, buffer, counter);
    }

    close(fd_ttyO1);
    return 0;
}
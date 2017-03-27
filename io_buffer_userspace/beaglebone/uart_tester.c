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
#include <strings.h>

#define NUM_MSGS 200
#define BAUDRATE B115200

int fd_ttyO1 = -1;

void quitHandler(int s) {
    if(fd_ttyO1 != -1) close(fd_ttyO1);
    printf("Quit\n"); // maybe add some stats later.
    exit(1);
}

void handleIO(int s) {
    printf("RECEIVED UART INTERRUPT\n");
}

int main(){
    // register signal handler to quit the program
    struct sigaction stopHandler;
    stopHandler.sa_handler = quitHandler;
    stopHandler.sa_flags = 0;
    sigemptyset(&stopHandler.sa_mask);
    sigaction(SIGINT, &stopHandler, NULL);

    printf("Starting uart tester\n");
    fd_ttyO1 = open("/dev/ttyO1",O_RDWR | O_NOCTTY);
    if(fd_ttyO1 == -1) {
        printf("Error opening ttyO1\n");
        return -1;
    } else printf("Opened ttyO1\n");

    // sync
    fcntl(fd_ttyO1, F_SETFL, 0);

    struct termios config;
    // get current settings of serial port
    if(tcgetattr(fd_ttyO1, &config) == -1) {
        printf("Not able to get attributes\n");
    }

    // adjust baud rate
    if(cfsetispeed(&config, (speed_t)BAUDRATE) == -1) {
        printf("Not able to set ctfo speed\n");
    }
    if(cfsetospeed(&config, (speed_t)BAUDRATE) == -1) {
        printf("Not able to set ctfi speed\n");
    }

    // adjust bit settings
    config.c_cflag |= (CLOCAL | CREAD);
    // set 8N1
    config.c_cflag &= ~PARENB;
    config.c_cflag &= ~CSTOPB;
    config.c_cflag &= ~CSIZE;
    config.c_cflag |= CS8;

    // reading data
    config.c_cc[VMIN] = 10; // if we receive more than 255 bytes we might lose some
    config.c_cc[VTIME] = 0;

    // apply the settings
    tcflush(fd_ttyO1, TCIFLUSH);
    if(tcsetattr(fd_ttyO1, TCSANOW | TCSAFLUSH, &config) == -1) {
        printf("Not able to set tio attributes\n");
    }

    // 1 byte buffer
    char buffer[1];
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
/*
This program will read input data received on UART1
on the BeagleBone and count how many packages are
received. The message counter will be compared with
the expected message count NUM_MSGS. On UART1 there
is an Arduino connected which will send NUM_MSGS.
*/
#define _POSIX_SOURCE // signal
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <strings.h>
#include "connector.h"

#define NUM_MSGS 5000

int fd_ttyO1 = -1;

void quitHandler(int s) {
    close(fd_ttyO1);
    printf("Quit\n"); // maybe add some stats later.
    exit(1);
}

void handleIO(int s) {
    printf("RECEIVED UART INTERRUPT\n");
}

int main(){
    // register signal handler to quit the program
    struct sigaction stopHandler = {
        .sa_handler = quitHandler,
        .sa_flags = 0
    };
    sigemptyset(&stopHandler.sa_mask);
    sigaction(SIGINT, &stopHandler, NULL);

    // SIGIO handler
    /*struct sigaction ioHandler;
    ioHandler.sa_handler = handleIO;
    ioHandler.sa_flags = 0;
    ioHandler.sa_restorer = NULL;
    sigemptyset(&ioHandler.sa_mask);
    sigaction(SIGIO, &ioHandler, NULL);*/

    /* allow the process to receive SIGIO */
    // fcntl(fd_ttyO1, F_SETOWN, getpid());

    printf("Starting uart tester\n");

    fd_ttyO1 = connectToSerial("/dev/ttyO1");
    if(fd_ttyO1 == -1) {
        printf("Error opening ttyO1\n");
        return -1;
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

    disconnectFromSerial(fd_ttyO1);
    return 0;
}
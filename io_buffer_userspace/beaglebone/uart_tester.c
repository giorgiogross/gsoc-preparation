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
#include "filelog.h"

#define NUM_MSGS 5000 // to compare to actual message count

static int fd_ttyO1 = -1;
static int fd_logfile = -1; 

void quitHandler(int s) {
    close(fd_ttyO1);
    close(fd_logfile);
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

    // SIGIO handler (for future tests)
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

    fd_logfile = createFile("/home/debian/gsoc/preparation/logfile");
    
    // 1 byte buffer
    char buffer[1];
    ssize_t counter = 0;

    // exit with ctrl+c
    for(;;) {
        ssize_t readAmnt = read(fd_ttyO1, buffer, sizeof(buffer));
        if(readAmnt == -1) {
            printf("error while reading serial\n");
            continue;
        }

        counter += readAmnt;
        printf("Read %d bytes: %s           #total until now: %d\n", readAmnt, buffer, counter);

        // save the message to the log file
        logMessage(fd_logfile, buffer, readAmnt);
    }

    close(fd_ttyO1);
    close(fd_logfile);

    return 0;
}
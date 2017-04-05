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

static int fd_ttyO0 = -1;
static int fd_ttyO1 = -1;
static int fd_ttyO2 = -1;
static int fd_ttyO4 = -1;

static int fd_logfile0 = -1; 
static int fd_logfile1 = -1; 
static int fd_logfile2 = -1; 
static int fd_logfile4 = -1; 

void quitHandler(int s) {
    close(fd_ttyO0);
    close(fd_ttyO1);
    close(fd_ttyO2);
    close(fd_ttyO4);

    close(fd_logfile0);
    close(fd_logfile1);
    close(fd_logfile2);
    close(fd_logfile4);

    printf("Quit\n"); // maybe add some stats later.
    exit(1);
}

void handleIO(int s) {
    printf("RECEIVED UART INTERRUPT\n");
}

void printAndLog(int fd, char* buffer, int size, int fd_logfile, ssize_t* msg_counter){
    ssize_t readAmnt = read(fd, buffer, size);
    if(readAmnt == -1) {
        printf("error while reading serial\n");
        return;
    }

    msg_counter += readAmnt;
    printf("Read %zd bytes: %s           #total until now: %zd\n", readAmnt, buffer, msg_counter);

    if(fd_logfile < 0) return;
    // save the messages to the log file
    logMessage(fd_logfile, buffer, readAmnt);
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

    fd_ttyO0 = connectToSerial("/dev/ttyO0");
    if(fd_ttyO1 == -1) {
        printf("Error opening ttyO0\n");
        return -1;
    }

    fd_ttyO1 = connectToSerial("/dev/ttyO1");
    if(fd_ttyO1 == -1) {
        printf("Error opening ttyO1\n");
        return -1;
    }

    fd_ttyO2 = connectToSerial("/dev/ttyO2");
    if(fd_ttyO1 == -1) {
        printf("Error opening ttyO2\n");
        return -1;
    }

    fd_ttyO4 = connectToSerial("/dev/ttyO4");
    if(fd_ttyO1 == -1) {
        printf("Error opening ttyO4\n");
        return -1;
    }

    fd_logfile0 = createFile("/home/debian/gsoc/preparation/logfile_UART0");
    fd_logfile1 = createFile("/home/debian/gsoc/preparation/logfile_UART1");
    fd_logfile2 = createFile("/home/debian/gsoc/preparation/logfile_UART2");
    fd_logfile4 = createFile("/home/debian/gsoc/preparation/logfile_UART4");
    
    // 1 byte buffer
    char buffer[1];
    ssize_t counter = 0;
    for(;;) { // exit with ctrl+c
        printAndLog(fd_ttyO0, buffer, sizeof(buffer), fd_logfile0, &counter);
        printAndLog(fd_ttyO1, buffer, sizeof(buffer), fd_logfile1, &counter);
        printAndLog(fd_ttyO2, buffer, sizeof(buffer), fd_logfile2, &counter);
        printAndLog(fd_ttyO4, buffer, sizeof(buffer), fd_logfile4, &counter);
    }
    
    close(fd_ttyO0);
    close(fd_ttyO1);
    close(fd_ttyO2);
    close(fd_ttyO4);

    close(fd_logfile0);
    close(fd_logfile1);
    close(fd_logfile2);
    close(fd_logfile4);

    return 0;
}

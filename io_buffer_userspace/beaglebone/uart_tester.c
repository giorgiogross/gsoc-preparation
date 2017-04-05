/*
    gsoc-preparation  Serial port communication and web servers on BeagleBone Black
    Copyright (C) 2017  Giorgio Gross   <contact@giorgio-gross.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
This program will read input data received on logfile_UART1
UART2, UART 4 and UART5 on the BeagleBone and count how many 
packages are received. The messages are then written to four
different files.
*/
#define _POSIX_SOURCE // signal
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <strings.h>
#include "connector.h"
#include "filelog.h"

static int fd_ttyO1 = -1;
static int fd_ttyO2 = -1;
static int fd_ttyO4 = -1;
static int fd_ttyO5 = -1;

static int fd_logfile1 = -1; 
static int fd_logfile2 = -1; 
static int fd_logfile4 = -1; 
static int fd_logfile5 = -1; 

void quitHandler(int s) {
    close(fd_ttyO1);
    close(fd_ttyO2);
    close(fd_ttyO4);
    close(fd_ttyO5);

    close(fd_logfile1);
    close(fd_logfile2);
    close(fd_logfile4);
    close(fd_logfile5);

    // maybe add some stats later.
    exit(1);
}

void handleIO(int s) {
    printf("RECEIVED UART INTERRUPT\n");
}

void printAndLog(int fd, char* buffer, int size, int fd_logfile, ssize_t* msg_counter);

int main(){
    // register signal handler to quit the program
    struct sigaction stopHandler = {
        .sa_handler = quitHandler,
        .sa_flags = 0
    };
    sigemptyset(&stopHandler.sa_mask);
    sigaction(SIGINT, &stopHandler, NULL);

    printf("Starting uart tester\n");

    fd_ttyO5 = connectToSerial("/dev/ttyO5");
    if(fd_ttyO5 == -1) {
        printf("Error opening ttyO5\n");
        return -1;
    }

    fd_ttyO1 = connectToSerial("/dev/ttyO1");
    if(fd_ttyO1 == -1) {
        printf("Error opening ttyO1\n");
        close(fd_ttyO5);
        return -1;
    }

    fd_ttyO2 = connectToSerial("/dev/ttyO2");
    if(fd_ttyO2 == -1) {
        printf("Error opening ttyO2\n");
        close(fd_ttyO5);
        close(fd_ttyO1);
        return -1;
    }

    fd_ttyO4 = connectToSerial("/dev/ttyO4");
    if(fd_ttyO4 == -1) {
        printf("Error opening ttyO4\n");
        close(fd_ttyO5);
        close(fd_ttyO1);
        close(fd_ttyO2);
        return -1;
    }

    fd_logfile1 = createFile("/home/debian/gsoc/preparation/serial/logfile_UART1");
    fd_logfile2 = createFile("/home/debian/gsoc/preparation/serial/logfile_UART2");
    fd_logfile4 = createFile("/home/debian/gsoc/preparation/serial/logfile_UART4");
    fd_logfile5 = createFile("/home/debian/gsoc/preparation/serial/logfile_UART5");
    
    // 1 byte buffer
    char buffer[255];
    ssize_t counter = 0;
    for(;;) { // exit with ctrl+c
        printAndLog(fd_ttyO1, buffer, sizeof(buffer), fd_logfile1, &counter);
        memset(&buffer, 0, sizeof(buffer));
        printAndLog(fd_ttyO2, buffer, sizeof(buffer), fd_logfile2, &counter);
        memset(&buffer, 0, sizeof(buffer));
        printAndLog(fd_ttyO4, buffer, sizeof(buffer), fd_logfile4, &counter);
        memset(&buffer, 0, sizeof(buffer));
        printAndLog(fd_ttyO5, buffer, sizeof(buffer), fd_logfile5, &counter);
        memset(&buffer, 0, sizeof(buffer));
    }
    
    close(fd_ttyO1);
    close(fd_ttyO2);
    close(fd_ttyO4);
    close(fd_ttyO5);

    close(fd_logfile1);
    close(fd_logfile2);
    close(fd_logfile4);
    close(fd_logfile5);

    return 0;
}


void printAndLog(int fd, char* buffer, int size, int fd_logfile, ssize_t* msg_counter){
    ssize_t readAmnt = read(fd, buffer, size);
    if(readAmnt == -1) {
        printf("error while reading serial\n");
        return;
    }
    *msg_counter += readAmnt;
    printf("Read %d bytes: %s           #total until now: %d\n", readAmnt, buffer, *msg_counter);
    printf("First char: %c   -   Last char: %c\n\n", buffer[0], buffer[readAmnt-1]);

    if(fd_logfile < 0) return;
    // save the messages to the log file
    logMessage(fd_logfile, buffer, readAmnt);
}
#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

/**
Open the deice and configure it.

@param  device_node     path to device node
@return file descriptor of the device
*/
int connectToSerial(char* device_node);

/**
Closes the passed file descriptor.

@param  fd              the file decriptor to be closed
*/
void disconnectFromSerial(int fd);

#endif
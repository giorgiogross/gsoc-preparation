#ifndef FILELOG_H
#define FILELOG_H

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/**
Opens and crates a new file of it is not existing

@param  path        path to file
@return the file descriptor
*/
int createFile(char* path);

/**
Writes the buffer to a file (new line) and adds
time stamps to each new line

@param  fd          file descriptor
@param  buf         bufferocntent
@param  size        buffersize
@return 0 on success, -1 otherwise
*/
int logMessage(int fd, char* buf, int size);

#endif
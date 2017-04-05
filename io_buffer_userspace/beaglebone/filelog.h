/*
    gsoc-preparation  Serial port communication and web servers on BeagleBone Black
    Copyright (C) 2017  Giorgio Gross

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
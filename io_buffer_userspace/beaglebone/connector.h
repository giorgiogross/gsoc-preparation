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
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

#include "libtest.h"
#include <unistd.h>

void printHello() {
    printf("Hello, this is printed when the static library is called\n");
}

int add(int a, int b) {
    return a+b;
}

void multiplyWith2(int* a) {
    *a = *a * 2;
}

void makeCallback(void (*callback)(char*, void*), void* fci) {
    // just call the callback;
    callback("Callback called\n", fci);
}

void registerObserver(void (*callback)(char*, void*), void* fci) {
    // wait some time to pretend a blocking operation
    sleep(10000);

    // call the callback; Can be used to notify others later (e.g. in my GSoC project) 
    // about file changes or if new I/O is there to read
    callback("A file changed\n", fci);
}

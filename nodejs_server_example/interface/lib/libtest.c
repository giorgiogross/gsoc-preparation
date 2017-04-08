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
Simple shared library with some functions to get experience in creating libraies.
*/
#include <unistd.h>
#include "libtest.h"
#include "c_exchange.h"

/*
Print a string
*/
void printHello() {
    printf("Hello, this is printed when the static library is called\n");
}

/*
Calculate a+b

@param a        first value
@param b        second value
@return result
*/
int add(int a, int b) {
    return a+b;
}

/*
Multiply the value saved in a with 2

@param a        pointer to the variable which will be doubled
@return void
*/
void multiplyWith2(int* a) {
    *a = *a * 2;
}

/*
Simple synchronous callback.

@param callback     pointer to the Exchange object which will be called
*/
void makeCallback(void* callback) {
    // just call the callback;
    pass(callback, "Callback called\n");
}


/*
Simple async callback.

@param callback     pointer to the Exchange object which will be called
*/
void doAsyncOperation(void* callback) {
    // wait some time to pretend a blocking operation
    sleep(10);

    // call the callback; Can be used to notify others later (e.g. in my GSoC project) 
    // about file changes or if new I/O is there to read
    pass(callback, "A file changed\n");
}

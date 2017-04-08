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
Simple static library with some functions to get experience in creating libraies.
*/
#include <stdio.h>

/*
Print a string
*/
void printHello(void);

/*
Calculate a+b

@param a        first value
@param b        second value
@return result
*/
int add(int a, int b);

/*
Multiply the value saved in a with 2

@param a        pointer to the variable which will be doubled
@return void
*/
void multiplyWith2(int* a);

/*
Simple synchronous callback.

@param callback     pointer to the function which will be called upon completion
@param fci          some value to pass to the function
*/
void makeCallback(void (*callback)(char*, void*), void* fci);

/*
Simple async callback which pretends to do a blocking operation

@param callback     pointer to the function which will be called upon completion
@param fci          some value to pass to the function
*/
void registerObserver(void (*callback)(char*, void*), void* fci);
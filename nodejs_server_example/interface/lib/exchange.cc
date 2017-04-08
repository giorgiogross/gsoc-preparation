#include "exchange.h"

/*
Pass the data on to the specified callback hold by the Exchanger pointed to by exchanger

@param exchanger    Exchange object which holds the actual callback
*/
void pass(void * exchanger, char* data) {
    Exchange * x = (Exchange *) exchanger;
    x->send(data); // leads to execution of the function passed to the constructor in c_wrapper.cc
}
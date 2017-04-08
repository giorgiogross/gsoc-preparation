#include "exchange.h"

void pass(void * exchanger, char* data) {
    Exchange * x = (Exchange *) exchanger;
    x->send(data); // leads to execution of the function passed to the constructor in c_wrapper.cc
}
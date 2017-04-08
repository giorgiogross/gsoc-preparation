
#include "libtest.h"
#include <stdio.h>

void observer(char* msg) {
    printf("%s", msg);
}

int main() {
    printHello();
    registerObserver(&observer);
    return 0;
}
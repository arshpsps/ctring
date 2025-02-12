#include "ctring.h"
#include <iostream>

int main() {
    char *s = "hello bkl";
    Ctring *c = ctring(s);

    char uwu = (*c)[0];
    std::cout << uwu << "\n";
}

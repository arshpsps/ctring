#include "ctring.h"
#include <iostream>

int main() {
    char *s = "hello bkl";
    Ctring *c = ctring(s);

    char uwu = (*c)[-9];
    std::cout << uwu << "\n";
}

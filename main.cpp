#include <iostream>
#include "progressbar.h"

//A little dummy to slow down the progress bar
int dummy(int a) {
    return 1+a;
}

int main(int argc, char *argv[])
{
    long elements = 10000;
    std::string label = "Hello from libProgress!";

    ProgressBar<long> p(elements, label);

    for(int i = 0; i <= elements; ++i) {
        p.update(i);
        for(int j = 0; j < 100000; ++j) {
            dummy(j);
        }
    }
    return 0;
}


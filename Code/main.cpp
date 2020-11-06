#include <iostream>
#include <vector>
#include "Matrix.h"
#include <Pipeline.h>
#include "Clipping.cpp"

int main() {

    
    Matrix m(3, 3, {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    });
    std::cout << "Hello" << std::endl;
}
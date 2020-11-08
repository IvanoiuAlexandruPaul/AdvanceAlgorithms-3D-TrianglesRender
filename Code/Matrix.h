#include <vector>
#include <iostream>
#include "Vertex.h"

#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    Matrix(int rows, int cols, std::vector<std::vector<double>> mat);

    Matrix operator* (Matrix);
    Matrix operator+ (Matrix);

    double operator()(int row, int col);

    double operator[](int i); // TODO valutare se toglierlo.

private:
    int cols_;
    int rows_;
    std::vector<std::vector<double>> mat_;
};

#endif
#include <vector>
#include <iostream>
#include "Vertex.h"

#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    Matrix();
    Matrix(int rows, int cols, std::vector<std::vector<double>> mat);
    Matrix operator* (Matrix);
    Vertex operator* (Vertex);
    Matrix operator+ (Matrix);

    double operator()(int row, int col);

    double operator[](int i); // TODO valutare se toglierlo.

    std::string str();

private:
    int cols_;
    int rows_;
    std::vector<std::vector<double>> mat_;
};

#endif
#include "Matrix.h"
#include <sstream>
#include <string>
#include <iostream>

Matrix::Matrix() {}

Matrix::Matrix(int rows, int cols, std::vector<std::vector<double>> mat) : rows_(rows), cols_(cols), mat_(mat) {
}

Matrix Matrix::operator*(Matrix b) { //Matrix Matrix::operator+(Matrix A)
    std::vector<std::vector<double>> result(
            4,
            std::vector<double>(4, 0));
    Matrix mat2_ = Matrix(4, 4, result);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            mat2_.mat_[i][j] = 0;
            for (int k = 0; k < cols_; ++k) {
                mat2_.mat_[i][j] += this->mat_[i][k] * b.mat_[k][j];
            }
        }
    }
    //  for(i = 0; i < r1; ++i)
    //     for(j = 0; j < c2; ++j)
    //         for(k = 0; k < c1; ++k)
    //         {
    //             mult[i][j] += a[i][k] * b[k][j];
    //         }

    return mat2_;
}

Matrix Matrix::operator+(Matrix b) {
    std::vector<std::vector<double>> result(
            4,
            std::vector<double>(4, 0));
    Matrix mat2_ = Matrix(4, 4, result);
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            mat2_.mat_[r][c] = this->mat_[r][c] + b.mat_[r][c];
        }
    }

    return mat2_;
}

/*
Matrix Matrix::sum(Matrix a, Matrix b)
{ //Matrix Matrix::operator+(Matrix A)
    std::vector<std::vector<double>> result(
        4,
        std::vector<double>(4, 0));
    Matrix mat2_ = Matrix(4, 4, result);
    for (int r = 0; r < rows_; ++r)
    {
        for (int c = 0; c < cols_; ++c)
        {
            mat2_.mat_[r][c] = a.mat_[r][c] + b.mat_[r][c];
        }
    }

    return mat2_;
}
*/

/*
Matrix Matrix::product(Matrix a, Matrix b)
{ //Matrix Matrix::operator*(Matrix A)
    std::vector<std::vector<double>> result(
        4,
        std::vector<double>(4, 0));
    Matrix mat2_ = Matrix(4, 4, result);
    for (int r = 0; r < a.rows_; ++r)
    {
        for (int c = 0; c < b.rows_; ++c)
        {
            for (int k = 0; k < a.cols_; ++k)
            {
                mat2_.mat_[r][c] += a.mat_[r][k] * b.mat_[k][c];
            }
        }
    }
    return mat2_;
}
*/

double Matrix::operator()(int row, int col) {
    // controllo row, col vanno bene
    try {
        if (row >= 0 && row <= rows_ && col >= 0 && col <= cols_)
            return mat_[row][col];
        else
            throw "Row and Col input parameters out of bounds.";
    }
    catch (const char *msg) {
        std::cout << msg << '\n';
    }

    return -1.0;
}

double Matrix::operator[](int i) {
    if (i >= 0 && i <= 3)
        return mat_[i][0];
    if (i >= 4 && i <= 7)
        return mat_[i][1];
    if (i >= 8 && i <= 11)
        return mat_[i][2];
    if (i >= 12 && i <= 15)
        return mat_[i][3];

    return -1.0;
}

std::string Matrix::str() {
    std::stringstream ss;
    for (int r = 0; r < 4; ++r) {
        ss << "[";
        for (int c = 0; c < 4; ++c) {
            ss << mat_[r][c];
            if (c == 3) {
                ss << "]" << std::endl;
            } else {
                ss << ", ";
            }
        }
    }
    return ss.str();
}

Vertex Matrix::operator*(Vertex v) {
    double x = mat_[0][0] * v.get_x() + mat_[0][1] * v.get_y() + mat_[0][2] * v.get_z() + mat_[0][3] * v.get_w();
    double y = mat_[1][0] * v.get_x() + mat_[1][1] * v.get_y() + mat_[1][2] * v.get_z() + mat_[1][3] * v.get_w();
    double z = mat_[2][0] * v.get_x() + mat_[2][1] * v.get_y() + mat_[2][2] * v.get_z() + mat_[2][3] * v.get_w();
    double w = mat_[3][0] * v.get_x() + mat_[3][1] * v.get_y() + mat_[3][2] * v.get_z() + mat_[3][3] * v.get_w();
    return Vertex(x, y, z, w);
}

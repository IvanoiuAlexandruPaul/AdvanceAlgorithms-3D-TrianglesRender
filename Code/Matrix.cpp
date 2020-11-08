#include "Matrix.h"

Matrix::Matrix() {}

Matrix::Matrix(int rows, int cols, std::vector<std::vector<double>> mat) : rows_(rows), cols_(cols), mat_(mat)
{
}

Matrix Matrix::operator*(Matrix b)
{ //Matrix Matrix::operator+(Matrix A)
    std::vector<std::vector<double>> result(
        4,
        std::vector<double>(4, 0));
    Matrix mat2_ = Matrix(4, 4, result);
    for (int r = 0; r < rows_; ++r)
    {
        for (int c = 0; c < cols_; ++c)
        {
            mat2_.mat_[r][c] = this->mat_[r][c] + b.mat_[r][c];
        }
    }

    return mat2_;
}

Matrix Matrix::operator+(Matrix b) {
    std::vector<std::vector<double>> result(
        4,
        std::vector<double>(4, 0));
    Matrix mat2_ = Matrix(4, 4, result);
    for (int r = 0; r < rows_; ++r)
    {
        for (int c = 0; c < cols_; ++c)
        {
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

double Matrix::operator()(int row, int col)
{
    // controllo row, col vanno bene
    try
    {
        if (row >= 0 && row <= rows_ && col >= 0 && col <= cols_)
            return mat_[row][col];
        else
            throw "Row and Col input parameters out of bounds.";
    }
    catch (const char *msg)
    {
        std::cout << msg << '\n';
    }

    return -1.0;
}

double Matrix::operator[](int i)
{
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
#include <vector>
#include <Vertex.h>
#include <vector>



class Matrix{
    // TODO implement matrix
    public: 
        Matrix(int rows, int cols, std::vector<std::vector<double>> mat){
            this->rows_ = rows;
            this->cols_ = cols;
            this->mat_ = mat;
        };
        
        Matrix product(Matrix a, Matrix b);
        Matrix sum(Matrix a, Matrix b);

        double Matrix::operator[](int i){
            if(i>=0 && i <= 3)
                return mat_[i][0];
            if(i>=4 && i <= 7)
                return mat_[i][1];
            if(i>=8 && i <= 11)
                return mat_[i][2];
            if(i>=12 && i <= 15)
                return mat_[i][3];
        }
      
    protected: 
        int cols_;
        int rows_;
        std::vector<std::vector<double>> mat_; 
};



Matrix Matrix::sum(Matrix a ,Matrix b){ //Matrix Matrix::operator+(Matrix A)     
    for(int r = 0; r < rows_; ++r){
        for(int c = 0; c < cols_; ++c){
             mat_[r][c] = a.mat_[r][c] + b.mat_[r][c];
        }
    }
}

Matrix Matrix::product(Matrix a , Matrix b){ //Matrix Matrix::operator*(Matrix A)     
     for(int r = 0; r < a.rows_; ++r){
        for(int c = 0; c < b.rows_; ++c){
            for(int k = 0; k < a.cols_; ++k){
                mat_[r][c] += a.mat_[r][k] * b.mat_[k][c];
            }
        }   
    }
}






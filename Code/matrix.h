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
        
        Matrix product(Matrix a ,Matrix b){ //Matrix Matrix::operator*(Matrix A)     
            for(int r = 0; r < a.rows_; ++r)
                for(int c = 0; c < b.rows_; ++j)
                    for(int k = 0; k < a.cols_; ++k){
                        mat[i][j] += a[r][] * b[k][j];
                    }
            }

    private:
        

    protected: 
        int cols_;
        int rows_;
        std::vector<std::vector<double>> mat_; 
};

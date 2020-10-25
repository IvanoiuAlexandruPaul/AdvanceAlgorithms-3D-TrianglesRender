#include <vector>
#include <Vertex.h>



class Matrix{
    // TODO implement matrix
    public: 
        Matrix(int rows, int cols){
            this->rows_ = rows;
            this->cols_ = cols;
        };

    
    private:
        int cols_;
        int rows_;
};
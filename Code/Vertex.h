#include<vector.h>

class Vertex {
    // TODO implement vector
    public:
        Vertex(double x, double y, double z, double w){
            this->x_=x;
            this->y_=y;
            this->z_=z;
            this->w_=w;
        }
    private:
        double x_, y_, z_, w_;
}
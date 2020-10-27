#include<vector>

class Vertex {
    // TODO implement vector
    public: 

        Vertex(double x, double y, double z){
            Vertex(x,y,z,1);
        }

        Vertex(double x, double y, double z, double w){
            this->x_=x;
            this->y_=y;
            this->z_=z;
            this->w_=w;
        }
        
        double get_x(){
            return this->x_;
        }
        double get_y(){
            return this->y_; 
        }
        double get_z(){
            return this->z_;
        }
        double get_w(){
            return this->w_; 
        }

    private:
        double x_, y_, z_, w_;
};
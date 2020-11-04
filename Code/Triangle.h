#include <Matrix.h>

class Triangle {

    public:
        Triangle();

        Triangle(Vertex normals, Vertex a, Vertex b, Vertex c, Vertex a_uv, Vertex b_uv, Vertex c_uv);

        Triangle(Vertex a, Vertex b, Vertex c){
                this->a = a; 
                this->b = b; 
                this->c = c;  
        }

        Vertex get_a(){
            return this->a;
        }

        Vertex get_b(){
            return this->b; 
        }
        
        Vertex get_c(){
            return this->c;
        }

        Vertex get_a_uv(){
            return this->c;
        }

        Vertex get_b_uv(){
            return this->c;
        }

        Vertex get_c_uv(){
            return this->c;
        }

        std::vector<Vertex> get_vertex(){
            return  {this->a,this->b,this->c};
        }

    private:
        Vertex normals;
        Vertex a;
        Vertex b;
        Vertex c;
        Vertex a_uv;
        Vertex b_uv;
        Vertex c_uv;
};
#include <vector>
#include <math.h>
#include "Triangle.h"

class ModelTransform
{
public:
    std::vector<Triangle> apply(std::vector<Triangle> triangles, Matrix mt)
    {
        std::vector<Triangle> new_triangles;
        for (Triangle t : triangles)
        {
            std::vector<Vertex> nv;
            for (Vertex v : t.get_vertex())
            {
                Matrix vc = Matrix(4, 1, {{v.get_x()}, {v.get_y()}, {v.get_z()}, {v.get_w()}});
                Matrix nc = mt.product(mt, vc);
                nv.push_back({nc(0, 0), nc(1, 0), nc(2, 0)});
            }
            new_triangles.push_back({nv.at(0), nv.at(1), nv.at(2)});
        }
        return new_triangles;
    }

    std::vector<Triangle> translation(std::vector<Triangle> triangles, Vertex vector)
    {
        return apply(triangles, Matrix(4, 4,
                                       {{1, 0, 0, vector.get_x()},
                                        {0, 1, 0, vector.get_y()},
                                        {0, 0, 1, vector.get_z()},
                                        {0, 0, 0, vector.get_w()}}));
    }

    std::vector<Triangle> rotationX(std::vector<Triangle> triangles, double theta)
    {
        return apply(triangles, Matrix(4, 4,
                                       {{1, 0, 0, 0},
                                        {0, cos(theta), -sin(theta), 0},
                                        {0, sin(theta), cos(theta), 0},
                                        {0, 0, 0, 1}}));
    }

    std::vector<Triangle> rotationY(std::vector<Triangle> triangles, double theta)
    {
        return apply(triangles, Matrix(4, 4,
                                       {{cos(theta), 0, sin(theta), 0},
                                        {0, 1, 0, 0},
                                        {-sin(theta), 0, cos(theta), 0},
                                        {0, 0, 0, 1}}));
    }

    std::vector<Triangle> rotationZ(std::vector<Triangle> triangles, double theta)
    {
        return apply(triangles, Matrix(4, 4,
                                       {{cos(theta), -sin(theta), 0, 0},
                                        {sin(theta), cos(theta), 0, 0},
                                        {0, 0, 1, 0},
                                        {0, 0, 0, 1}}));
    }

    std::vector<Triangle> scale(std::vector<Triangle> triangles, Vertex vector)
    {
        return apply(triangles, Matrix(4, 4,
                                       {{vector.get_x(), 0, 0, 0},
                                        {0, vector.get_y(), 0, 0},
                                        {0, 0, vector.get_z(), 0},
                                        {0, 0, 0, vector.get_w()}}));
    }

    /* 
        std::vector<Triangle> translation(std::vector<Triangle> triangles, Vertex vector){
            std::vector<Triangle> new_triangles; 
            for(Triangle t:triangles){
                std::vector<Vertex> nv; 
                
                for(Vertex v: t.get_vertex()){
                    Matrix mt = Matrix(4, 4, 
                        {{1,0,0, vector.get_x()},
                         {0,1,0, vector.get_y()},
                         {0,0,1, vector.get_z()},
                         {0,0,0, vector.get_w()}
                         });
                    Matrix vc = Matrix(4,1,{{v.get_x()},{v.get_y()},{v.get_z()},{v.get_w()}});
                    Matrix nc = mt.product(mt,vc); 
                    nv.push_back({nc(0,0),nc(1,0),nc(2,0)}); 
                }
                new_triangles.push_back({nv.at(0),nv.at(1),nv.at(2)}); 
            }
            return new_triangles;
        }

        
        std::vector<Triangle> rotationX(std::vector<Triangle> triangles,  double theta){
            std::vector<Triangle> new_triangles; 
            for(Triangle t:triangles){  
                std::vector<Vertex> nv; 
                for(Vertex v: t.get_vertex()){
                    Matrix vc = Matrix(4,1,{{v.get_x()},{v.get_y()},{v.get_z()},{v.get_w()}});
                    Matrix rotation_x = Matrix(4, 4, 
                            {{1, 0, 0, 0},
                            {0, cos(theta), -sin(theta), 0},
                            {0, sin(theta), cos(theta), 0},
                            {0, 0, 0, 1}
                            });    
                    Matrix nc = rotation_x.product(rotation_x,vc); 
                    nv.push_back({nc(0,0),nc(1,0),nc(2,0)}); 
                }
                new_triangles.push_back({nv.at(0),nv.at(1),nv.at(2)}); 
            }
            return new_triangles;
        }

        std::vector<Triangle> rotationY(std::vector<Triangle> triangles,  double theta){
            std::vector<Triangle> new_triangles; 
            for(Triangle t:triangles){
                std::vector<Vertex> nv; 
                for(Vertex v: t.get_vertex()){
                    Matrix vc = Matrix(4,1,{{v.get_x()},{v.get_y()},{v.get_z()},{v.get_w()}});
                    Matrix rotation_y = Matrix(4, 4, 
                            {{cos(theta), 0, sin(theta), 0},
                            {0, 1, 0, 0},
                            {-sin(theta), 0, cos(theta), 0},
                            {0, 0, 0, 1}
                            });
                    Matrix nc = rotation_y.product(rotation_y,vc); 
                    nv.push_back({nc(0,0),nc(1,0),nc(2,0)}); 
                }
                new_triangles.push_back({nv.at(0),nv.at(1),nv.at(2)}); 
            }
            return new_triangles;
        }
        
        std::vector<Triangle> rotationZ(std::vector<Triangle> triangles,  double theta){
            std::vector<Triangle> new_triangles; 
            for(Triangle t:triangles){
                std::vector<Vertex> nv; 
                for(Vertex v: t.get_vertex()){
                    Matrix vc = Matrix(4,1,{{v.get_x()},{v.get_y()},{v.get_z()},{v.get_w()}});
                    Matrix rotation_z = Matrix(4, 4, 
                            {{cos(theta), -sin(theta),0, 0},
                            {sin(theta), cos(theta), 0, 0},
                            {0, 0, 1, 0},
                            {0, 0, 0, 1}
                            }); 
                    Matrix nc = rotation_z.product(rotation_z,vc); 
                    nv.push_back({nc(0,0),nc(1,0),nc(2,0)}); 
                }
                new_triangles.push_back({nv.at(0),nv.at(1),nv.at(2)}); 
            }
            return new_triangles;
        }
    
        std::vector<Triangle> scale(std::vector<Triangle> triangles, Vertex vector){
            std::vector<Triangle> new_triangles; 
            for(Triangle t:triangles){
                std::vector<Vertex> nv; 
                for(Vertex v: t.get_vertex()){
                    Matrix mt = Matrix(4, 4, 
                        {{vector.get_x(), 0, 0, 0},
                        {0, vector.get_y(), 0, 0},
                        {0, 0, vector.get_z(), 0},
                        {0, 0, 0, vector.get_w()}
                        });
                    Matrix vc = Matrix(4,1,{{v.get_x()},{v.get_y()},{v.get_z()},{v.get_w()}});
                    Matrix nc = mt.product(mt,vc); 
                    nv.push_back({nc(0,0),nc(1,0),nc(2,0)}); 
                }
                new_triangles.push_back({nv.at(0),nv.at(1),nv.at(2)}); 
            }
            return new_triangles;
        }
    */
private:
};
#include "ModelTransform.h"

std::vector<Triangle> ModelTransform::apply(std::vector<Triangle> triangles, Matrix mt)
{
    std::vector<Triangle> new_triangles;
    for (Triangle t : triangles)
    {
        std::vector<Vertex> nv;
        for (Vertex v : t.get_vertex())
        {
            Matrix vc = Matrix(4, 1, {{v.get_x()}, {v.get_y()}, {v.get_z()}, {v.get_w()}});
            Matrix nc = mt * vc;
            nv.push_back({nc(0, 0), nc(1, 0), nc(2, 0)});
        }
        new_triangles.push_back({nv.at(0), nv.at(1), nv.at(2)});
    }
    return new_triangles;
}

std::vector<Triangle> ModelTransform::translation(std::vector<Triangle> triangles, Vertex vector)
{
    return apply(triangles, Matrix(4, 4,
                                   {{1, 0, 0, vector.get_x()},
                                    {0, 1, 0, vector.get_y()},
                                    {0, 0, 1, vector.get_z()},
                                    {0, 0, 0, vector.get_w()}}));
}

std::vector<Triangle> ModelTransform::rotationX(std::vector<Triangle> triangles, double theta)
{
    return apply(triangles, Matrix(4, 4,
                                   {{1, 0, 0, 0},
                                    {0, cos(theta), -sin(theta), 0},
                                    {0, sin(theta), cos(theta), 0},
                                    {0, 0, 0, 1}}));
}

std::vector<Triangle> ModelTransform::rotationY(std::vector<Triangle> triangles, double theta)
{
    return apply(triangles, Matrix(4, 4,
                                   {{cos(theta), 0, sin(theta), 0},
                                    {0, 1, 0, 0},
                                    {-sin(theta), 0, cos(theta), 0},
                                    {0, 0, 0, 1}}));
}

std::vector<Triangle> ModelTransform::rotationZ(std::vector<Triangle> triangles, double theta)
{
    return apply(triangles, Matrix(4, 4,
                                   {{cos(theta), -sin(theta), 0, 0},
                                    {sin(theta), cos(theta), 0, 0},
                                    {0, 0, 1, 0},
                                    {0, 0, 0, 1}}));
}

std::vector<Triangle> ModelTransform::scale(std::vector<Triangle> triangles, Vertex vector)
{
    return apply(triangles, Matrix(4, 4,
                                   {{vector.get_x(), 0, 0, 0},
                                    {0, vector.get_y(), 0, 0},
                                    {0, 0, vector.get_z(), 0},
                                    {0, 0, 0, vector.get_w()}}));
}
#include "Projection.h"
#include <math.h>

Projection::Projection(float left, float right, float top, float bottom, float near, float far)
        : mt(4, 4, {
        {2.0 * near / (right - left), 0                           , -(right + left) / (right - left)  , 0                                 },
        {0                          , 2.0 * near / (bottom - top) , -(bottom + top) / (bottom - top)  , 0                                 },
        {0                          , 0                           , (far + near) / (far - near)       , (-2.0 * far * near) / (far - near)},
        {0                          , 0                           , 1.0                               , 0                                 }
}) {
    // std::vector<std::vector<double>> result(4, std::vector<double>(4, 0));
    // result[0][0] = 2.0f * near / (right - left);
    // result[0][3] = (right + left) / (right - left);
    // result[1][1] = 2.0f * near / (top - bottom);
    // result[1][2] = (top + bottom) / (top - bottom);
    // result[1][3] = -(far + near) / (far - near);
    // result[2][3] = -2.0f * far * near / (far - near);
    // result[3][3] = -1.0f;
    // //result[3][3] = 0.0f;
    // mt = Matrix(4, 4, result);
}

// Constructor for trigonometric
Projection::Projection(float fov, float aspect, float near, float far) {
    float focal = 1.0f / tan(fov / 2.0f); //cotan(fov/2)
    //in teoria dovrebbe essere ((height or width) / 2) * cotan(fov/2)
    std::vector<std::vector<double>> result(
            4,
            std::vector<double>(4, 0));
    result[0][0] = focal / aspect;
    result[1][1] = focal;
    result[2][2] = (far + near) / (near - far);
    result[3][3] = 2 * far * near / (near - far);
    result[3][2] = -1.0f;
    mt = Matrix(4, 4, result);
}

std::vector<Triangle> Projection::project(std::vector<Triangle> triangles) {
    std::vector<Triangle> new_triangles;
    // Matrix mt = perspective(-1.0f, 1.0f, 1.0f, -1.0f, 0.1f, 100.0f);
    new_triangles.reserve(triangles.size());
    for (Triangle t : triangles) {
//        std::vector<Vertex> nv;
//        for (Vertex v : t.get_vertex())
//        {
//            Matrix vc = Matrix(4, 1, {{v.get_x()}, {v.get_y()}, {v.get_z()}, {v.get_w()}});
//            Matrix nc = mt * vc;
//            nv.push_back({nc(0, 0), nc(1, 0), nc(2, 0)});
//        }
//        new_triangles.push_back({nv.at(0), nv.at(1), nv.at(2)});
         Vertex a = mt * t.get_a();
         Vertex b = mt * t.get_b();
         Vertex c = mt * t.get_c();
        Triangle triangle(a / a.get_w(), b / b.get_w(), c / c.get_w());
        new_triangles.emplace_back(triangle);
    }
    return new_triangles;
}


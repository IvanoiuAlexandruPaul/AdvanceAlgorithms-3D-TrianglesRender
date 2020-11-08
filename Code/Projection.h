#include <vector>
#include "Triangle.h"
#include "Matrix.h"
#ifndef PROJECTION_H
#define PROJECTION_H

class Projection
{

private:
    Matrix mt;

public:

    //perspective(-1.0f,1.0f,1.0f,-1.0f,0.1f,100.0f);
    Projection(float left, float right, float top, float bottom, float near, float far);

    //perspectiv3(π/2, (16.0f/9.0f), 0.1f, 100.0f);
    Projection(float fov, float aspect, float near, float far);

    std::vector<Triangle> project(std::vector<Triangle> triangles);
};

#endif
#include <vector>
#include <string>
#include "Vertex.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{

public:

    Triangle(Vertex a, Vertex b, Vertex c);

    Vertex get_a();

    Vertex get_b();

    Vertex get_c();

    std::vector<Vertex> get_vertex() const;

    std::string str();

private:
    Vertex a;
    Vertex b;
    Vertex c;
};

#endif
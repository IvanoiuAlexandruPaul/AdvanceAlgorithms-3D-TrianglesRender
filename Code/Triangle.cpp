#include "Triangle.h"

Triangle::Triangle(Vertex a, Vertex b, Vertex c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

Vertex Triangle::get_a()
{
    return this->a;
}

Vertex Triangle::get_b()
{
    return this->b;
}

Vertex Triangle::get_c()
{
    return this->c;
}

std::vector<Vertex> Triangle::get_vertex() const
{
    return {this->a, this->b, this->c};
}
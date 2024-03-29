#include "Triangle.h"
#include <sstream>

Triangle::Triangle(Vertex a, Vertex b, Vertex c) : a(a), b(b), c(c)
{
    /* this->a = a;
    this->b = b;
    this->c = c; */
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

std::string Triangle::str() {
    std::stringstream ss;
    ss << "<Triangle: " << a.str() << ", " << b.str() << ", " << c.str() << ", " <<  "|";
    return ss.str();

}
#include <string>


#ifndef VERTEX_H
#define VERTEX_H
class Vertex
{

public:
    Vertex();

    Vertex(double x, double y, double z);

    Vertex(double x, double y, double z, double w);

    Vertex(Vertex const & v);

    double get_x();
    double get_y();
    double get_z();
    double get_w();

    double operator[](int index);

    Vertex operator*(double r);

    double operator*(const Vertex&) const;

    double norm() const;


    Vertex operator-(Vertex r);

    Vertex operator+(Vertex r);

    Vertex operator/(double d);

    bool operator==(Vertex) const;

    std::string str();

private:
    double x_{};
    double y_{};
    double z_{};
    double w_{};
};
double angle(const Vertex& v1, const Vertex& v2);
Vertex lerp(Vertex a, Vertex b, double lerpAmt);


/**
 * Returns the 4D vector (x_p, y_p, z_p, w_p) representing plane 
 * P: x_p * x + z_p * z + y_p * y + w_p * w = 0
 */
Vertex planePassingPoints(Vertex a, Vertex b, Vertex c);
#endif
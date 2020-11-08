#include <vector>

class Vertex
{

public:
    Vertex()
    {
        Vertex(0, 0, 0, 1);
    }

    Vertex(double x, double y, double z)
    {
        Vertex(x, y, z, 1);
    }

    Vertex(double x, double y, double z, double w)
    {
        this->x_ = x;
        this->y_ = y;
        this->z_ = z;
        this->w_ = w;
    }

    double get_x()
    {
        return this->x_;
    }
    double get_y()
    {
        return this->y_;
    }
    double get_z()
    {
        return this->z_;
    }
    double get_w()
    {
        return this->w_;
    }

    double getElementVertex(int index)
    {
        switch (index)
        {
        case 0:
            return get_x();
        case 1:
            return get_y();
        case 2:
            return get_z();
        case 3:
            return get_w();
        default:
            break;
        }
    }

    Vertex operator*(double r)
    {
        return Vertex(x_ * r, y_ * r, z_ * r, w_ * r);
    }

    Vertex operator-(Vertex r)
    {
        return Vertex(x_ - r.get_x(), y_ - r.get_y(), z_ - r.get_z(), w_ - r.get_w());
    }

    Vertex operator+(Vertex r)
    {
        return Vertex(x_ + r.get_x(), y_ + r.get_y(), z_ + r.get_z(), w_ + r.get_w());
    }

private:
    double x_;
    double y_;
    double z_;
    double w_;
};

Vertex lerp(Vertex a, Vertex b, double lerpAmt)
{
    return ((b - a) * lerpAmt) + b;
}

/**
 * Returns the 4D vector (x_p, y_p, z_p, w_p) representing plane 
 * P: x_p * x + z_p * z + y_p * y + w_p * w = 0
 */
Vertex planePassingPoints(Vertex a, Vertex b, Vertex c)
{
    double x_p, y_p, z_p, w_p;

    // Calculate segment AB
    double x_ab = b.get_x() - a.get_x();
    double y_ab = b.get_y() - a.get_y();
    double z_ab = b.get_z() - a.get_z();

    // Calculate segment AC
    double x_ac = c.get_x() - a.get_x();
    double y_ac = c.get_y() - a.get_y();
    double z_ac = c.get_z() - a.get_z();

    x_p = y_ab * z_ac - y_ac * z_ab;
    y_p = x_ac * z_ab - x_ab * z_ac;
    z_p = x_ab * y_ac - y_ab * x_ac;
    w_p = (-x_p * x_ab - y_p * y_ab - z_p * z_ab);

    return Vertex(x_p, y_p, z_p, w_p);
}
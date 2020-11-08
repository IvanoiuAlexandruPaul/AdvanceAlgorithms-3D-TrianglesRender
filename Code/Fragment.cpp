#include "Fragment.h"

Fragment::Fragment(int pixel_x, int pixel_y, double z)
{
    this->pixel_x = pixel_x;
    this->pixel_y = pixel_y;
    this->z = z;
}

int Fragment::get_x() const
{
    return pixel_x;
}

int Fragment::get_y() const
{
    return pixel_y;
}

double Fragment::get_z() const
{
    return z;
}
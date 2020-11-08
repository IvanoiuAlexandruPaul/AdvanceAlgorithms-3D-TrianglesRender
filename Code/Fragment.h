#ifndef FRAGMENT_H
#define FRAGMENT_H

class Fragment
{
public:
    Fragment(int pixel_x, int pixel_y, double z);

    int get_x() const;

    int get_y() const;

    double get_z() const;

private:
    int pixel_x;
    int pixel_y;
    double z;
};

#endif
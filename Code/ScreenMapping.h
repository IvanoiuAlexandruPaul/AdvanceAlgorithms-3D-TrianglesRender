#ifndef SCREENMAPPING_H
#define SCREENMAPPING_H



// TODO Valutare se cambiare nome. Magari ScreenContext o ScreenManager?
class ScreenMapping
{
public:
    ScreenMapping(int screenWidth, int screenHeight);

    void mapScreenPixelsToCartesian(int screenx, int screeny, double *coordinateX, double *coordinateY);

    void mapCartesianToScreenPixels(double x, double y, double *pixelRow, double *pixelCol);

    int get_screenWidth();

    int get_screenHeight();

private:
    int screenWidth;
    int screenHeight;
};

#endif
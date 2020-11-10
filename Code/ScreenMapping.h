#ifndef SCREENMAPPING_H
#define SCREENMAPPING_H



// TODO Valutare se cambiare nome. Magari ScreenContext o ScreenManager?
class ScreenMapping
{
public:
    ScreenMapping(int screenWidth, int screenHeight);

    void mapScreenPixelsToCartesian(int pixelX, int pixelY, double *cartX, double *cartY);

    void mapCartesianToScreenPixels(double cartX, double cartY, double *pixelX, double *pixelY);

    int screenWidth;
    int screenHeight;


};

#endif
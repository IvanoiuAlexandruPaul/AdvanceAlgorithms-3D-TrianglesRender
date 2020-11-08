#include "ScreenMapping.h"
#include <math.h>

ScreenMapping::ScreenMapping(int screenWidth, int screenHeight)
{
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
}

void ScreenMapping::mapScreenPixelsToCartesian(int screenx, int screeny, double *coordinateX, double *coordinateY)
{
    *coordinateX = screenx - screenWidth / 2;
    *coordinateY = -screeny + screenHeight / 2;
}

void ScreenMapping::mapCartesianToScreenPixels(double x, double y, double *pixelRow, double *pixelCol)
{
    *pixelRow = floor((screenWidth / 2) + x);
    *pixelCol = floor((screenHeight / 2) - y);
}

int ScreenMapping::get_screenWidth()
{
    return screenWidth;
}

int ScreenMapping::get_screenHeight()
{
    return screenHeight;
}

#include "ScreenMapping.h"
#include <math.h>

ScreenMapping::ScreenMapping(int screenWidth, int screenHeight) : screenHeight(screenHeight), screenWidth(screenWidth)
{
    /* this->screenHeight = screenHeight;
    this->screenWidth = screenWidth; */
}

double screenToCartesian(int screenCord, int screenDim) {
    return double(2 * screenCord) / double(screenDim - 1) - 1;
}

double cartesianToScreen(double cartCord, int screenDim) {
    return ((cartCord + 1) * double(screenDim - 1)) / 2.0;
}

void ScreenMapping::mapScreenPixelsToCartesian(int pixelX, int pixelY, double *cartX, double *cartY)
{
//    *cartX = (2 * pixelX / double(screenWidth - 1));
//    *cartY = (2 * pixelY / double(screenHeight - 1));
    *cartX = screenToCartesian(pixelX, screenWidth);
    *cartY = screenToCartesian(pixelY, screenHeight);
}

void ScreenMapping::mapCartesianToScreenPixels(double cartX, double cartY, double *pixelX, double *pixelY)
{
//    *pixelX = floor(cartX * (screenWidth - 1) / 2.0);
//    *pixelY = floor(cartY * (screenHeight - 1) / 2.0);
    *pixelX = floor(cartesianToScreen(cartX, screenWidth));
    *pixelY = floor(cartesianToScreen(cartY, screenHeight));
}
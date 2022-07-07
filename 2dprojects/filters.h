#ifndef FILTERS_H
#define FILTERS_H

#include "canvas2d.h"

class Filters
{
public:
    Filters();
    void filterBlur(Canvas2D& canvas, int radius);
    void filterEdgeDetect(Canvas2D& canvas, float sensitivity);
    void filterScale(Canvas2D& canvas, float x, float y);
};

#endif // FILTERS_H

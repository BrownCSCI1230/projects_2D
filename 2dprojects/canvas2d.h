#ifndef CANVAS2D_H
#define CANVAS2D_H

#include <QWidget>
#include "rgba.h"

class Canvas2D {
public:
    Canvas2D();

    void settingsChanged();

    void mouseDown(int x, int y);
    void mouseDragged(int x, int y);
    void mouseUp(int x, int y);

    void paint(int x, int y, std::vector<float> mask, bool smudge);

    void filterImage();

    // Return an array containing the rows of the image one after another, starting from the top.
    // Each row is width() wide and there are height() rows, so this array will have
    // width() * height() elements.
    RGBA *data() { return reinterpret_cast<RGBA *>(m_image->bits()); }

    // used by support code to provide access to canvas data
    void setImage(QImage* image);

private:
    QImage* m_image;
};

#endif // CANVAS2D_H

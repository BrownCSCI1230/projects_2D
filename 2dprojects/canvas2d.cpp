#include "canvas2d.h"
#include <vector>

Canvas2D::Canvas2D()
{
}

void Canvas2D::settingsChanged() {

}

void Canvas2D::mouseDown(int x, int y) {
    // Brush TODO: handle mouse events
}

void Canvas2D::mouseDragged(int x, int y) {
    // Brush TODO: handle mouse events
}

void Canvas2D::mouseUp(int x, int y) {
    // Brush TODO: handle mouse events
}

void Canvas2D::paint(int x, int y, std::vector<float> mask, bool smudge) {
    // Brush TODO: paint canvas using mask
}

void Canvas2D::filterImage() {
    // Filter TODO: filter the image on canvas using the selected filter
}

void Canvas2D::setImage(QImage* image) {
    m_image = image;
}

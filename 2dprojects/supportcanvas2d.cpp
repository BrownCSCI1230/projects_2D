#include "supportcanvas2d.h"
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <QMouseEvent>

SupportCanvas2D::SupportCanvas2D()
{
    m_image = new QImage(1, 1, QImage::Format_RGBX8888);
    m_canvas = Canvas2D();
    m_canvas.setImage(m_image);
}

SupportCanvas2D::~SupportCanvas2D() {
    delete m_image;
}

void SupportCanvas2D::resize(int width, int height) {
    // clamp negative sizes so we always have at least one pixel
    if (width < 1) width = 1;
    if (height < 1) height = 1;

    delete m_image;
    m_image = new QImage(width, height, QImage::Format_RGBX8888 /* this corresponds to the RGBA struct */);
    m_canvas.setImage(m_image);

    // set the new image to black
    memset(m_image->bits(), 0, width * height * sizeof(RGBA));
    for (int i = sizeof(RGBA)-1; (unsigned long) i < width * height * sizeof(RGBA); i+=sizeof(RGBA)) {
        m_image->bits()[i] = 255;
    }

    // resize and repaint the window (resizing the window doesn't always repaint it, like when you
    // set the same size twice)
    setFixedSize(width, height);
    update();
    notifySizeChanged(width, height);
}

bool SupportCanvas2D::loadImage(const QString &file) {
    QImage *temp = new QImage();
    bool success = false;

    if (temp->load(file)) {
        // Make sure the image is RGB (not monochrome, for example).
        if (temp->format() != QImage::Format_RGBX8888) {
            QImage *old = temp;
            temp = new QImage(old->convertToFormat(QImage::Format_RGBX8888));
            delete old;
        }

        // Show the new image.
        resize(temp->width(), temp->height());
        memcpy(m_canvas.data(), temp->bits(), temp->sizeInBytes());
        update();

        // Remember the filename so we can revert to it
        m_lastfile = file;
        success = true;
    }

    delete temp;
    return success;
}

bool SupportCanvas2D::saveImageFile(const QString &file) {
    return m_image->save(file, nullptr, -1);
}

void SupportCanvas2D::newImage() {
    // Load a black 500x500 image.
    resize(500, 500);
}

bool SupportCanvas2D::revertImage() {
    if (!m_lastfile.isNull()) {
        if (loadImage(m_lastfile)) {
            return true;
        }
        QMessageBox::critical(this, "Error", "Could not load image \"" + m_lastfile + "\"");
    }
    return false;
}

void SupportCanvas2D::clearImage() {
    resize(width(), height());
}

bool SupportCanvas2D::saveImage() {
    QString file = QFileDialog::getSaveFileName(this);
    if (!file.isNull()) {
        // Qt needs an extension to decide what format to save in, so make sure it gets one.
        if (!file.contains('.'))
            file += ".png";

        if (saveImageFile(file))
            return true;
        QMessageBox::critical(this, "Error", "Could not save image \"" + file + "\"");
    }
    return false;
}

void SupportCanvas2D::mousePressEvent(QMouseEvent *event) {
    m_canvas.mouseDown(event->position().x(), event->position().y());
    update();
}

void SupportCanvas2D::mouseMoveEvent(QMouseEvent *event) {
    m_canvas.mouseDragged(event->position().x(), event->position().y());
    update();
}

void SupportCanvas2D::mouseReleaseEvent(QMouseEvent *event) {
    // Move the mouse again in case this event is at a different position then the last event.
    mouseMoveEvent(event);
    m_canvas.mouseUp(event->position().x(), event->position().y());
    update();
}

void SupportCanvas2D::settingsChanged() {
    m_canvas.settingsChanged();
}



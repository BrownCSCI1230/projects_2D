#ifndef SUPPORTSupportCanvas2D_H
#define SUPPORTSupportCanvas2D_H

#include <QWidget>
#include "rgba.h"
#include "canvas2d.h"

class SupportCanvas2D : public QWidget{
    Q_OBJECT
public:
    SupportCanvas2D();
    ~SupportCanvas2D();

    // Resize the canvas (this will resize the window too and set the image to black)
    void resize(int width, int height);

    // Load or save the canvas given a specific file path.  Return true on success.
    bool loadImage(const QString &file);
    bool saveImageFile(const QString &file);

    // Load a black 500x500 image
    void newImage();

    // Show a file dialog and perform the save action if the user picks a file.  Return true on
    // success.
    bool saveImage();

public slots:
    bool revertImage();
    void clearImage();

protected:
    // Overridden from QWidget
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    // This will be called when the size of the canvas has been changed
    virtual void notifySizeChanged(int w, int h) = 0;

    // This will be called when the settings have changed
    virtual void settingsChanged();

    QImage *m_image;

private:
    QString m_lastfile;
    Canvas2D m_canvas;
};

#endif // SUPPORTCANVAS2D_H

#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class QMouseEvent;

namespace Ui {
class ScribbleArea;
}

class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    explicit ScribbleArea(QWidget *parent = nullptr);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char* fileFormat);

    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

public slots:
    void clearImage();
    void print();

protected:
    // Mouse events for implementing the drawing.
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    // For updating the scribble area
    void paintEvent(QPaintEvent* event) override;

    // For ensuring that QImage size > Widget size at all times.
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::ScribbleArea *ui;

    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage* image, const QSize &newSize);

    bool modified;      // True if file contains unsaved changes.
    bool scribbling;    // True while the user is pressing the mouse for scribbling.

    int myPenWidth;
    QColor myPenColor;

    QImage image;       // Stores image drawn by user.
    QPoint lastPoint;   // Last point the cursor moved/was pressed.
};

#endif // SCRIBBLEAREA_H

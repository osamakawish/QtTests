#include <QMouseEvent>
#include <QPainter>

#include "scribblearea.h"
#include "ui_scribblearea.h"

class QMouseEvent;

ScribbleArea::ScribbleArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScribbleArea)
{
    ui->setupUi(this);

    // All contents remain at the top-left of the window, without resizing when wingow is scaled.
    setAttribute(Qt::WA_StaticContents);

    // Initiating private members.
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
}

bool ScribbleArea::openImage(const QString &fileName)
{
    QImage loadedFile;
    if(!loadedFile.load(fileName)) return false;

    QSize newSize = loadedFile.size().expandedTo(size());
    resizeImage(&loadedFile, newSize);
    image = loadedFile; modified = false;
    update();

    return true;
}

bool ScribbleArea::saveImage(const QString &fileName, const char* fileFormat)
{
    // Q: What does fileFormat do?
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false; return true;
    } return false;
}

void ScribbleArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void ScribbleArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void ScribbleArea::clearImage()
{
    image.fill(QColor(255, 255, 255));
    modified = true; update();
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

// Not entirely sure why rectangles are being drawn. But will see what happens once this is finished.
void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect = event->rect();
    painter.drawImage(rect, image, rect);
}

// Make window size slightly larger than image size.
void ScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());

        // Passing image by reference to change its width and height.
        resizeImage(&image, QSize(newWidth, newHeight));

        update();
    }
    QWidget::resizeEvent(event);
}

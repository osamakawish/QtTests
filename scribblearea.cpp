#include "scribblearea.h"
#include "ui_scribblearea.h"

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
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(&fileName, fileFormat)) {
        modified = false; return true;
    } return false;
}


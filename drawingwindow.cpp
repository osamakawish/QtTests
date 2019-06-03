#include "drawingwindow.h"
#include "ui_drawingwindow.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>

DrawingWindow::DrawingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawingWindow)
{
    ui->setupUi(this);

    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);

    createActions(); createMenus();
    setWindowTitle("Scribble");
    resize(500,500);
}

void DrawingWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {event->accept();}
    else {event->ignore();}
}

void DrawingWindow::open()
{
    if (maybeSave()) {
        // Retrieve file name.
        QString filename = QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
        // Open file if name received.
        if (!filename.isEmpty()) {
            scribbleArea->openImage(filename);
        }
    }
}

// Not even the slightest clue as to what is going on here.
void DrawingWindow::save()
{
    QAction* action = qobject_cast<QAction*>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void DrawingWindow::penColor()
{
    QColor color = QColorDialog::getColor(scribbleArea->penColor());
    if (color.isValid()) { scribbleArea->setPenColor(color); }
}

void DrawingWindow::penWidth()
{
    bool ok;
    // Input dialog to select pen width between 1 and 50 with step 1.
    int width = QInputDialog::getInt(this,"Scribble","Select pen width",
                                     scribbleArea->penWidth(),1,50,1,&ok);
    // Change pen width based on input.
    if (ok) {
        scribbleArea->setPenWidth(width);
    }
}

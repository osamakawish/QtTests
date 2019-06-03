#include "drawingwindow.h"
#include "ui_drawingwindow.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>

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

void DrawingWindow::about()
{
    QMessageBox::about(this, tr("About Scribble"),
            tr("<p>The <b>Scribble</b> example shows how to use QMainWindow as the "
               "base widget for an application, and how to reimplement some of "
               "QWidget's event handlers to receive the events generated for "
               "the application's widgets:</p><p> We reimplement the mouse event "
               "handlers to facilitate drawing, the paint event handler to "
               "update the application and the resize event handler to optimize "
               "the application's appearance. In addition we reimplement the "
               "close event handler to intercept the close events before "
               "terminating the application.</p><p> The example also demonstrates "
               "how to use QPainter to draw an image in real time, as well as "
               "to repaint widgets.</p>"));
}

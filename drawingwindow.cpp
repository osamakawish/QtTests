#include "drawingwindow.h"
#include "ui_drawingwindow.h"

#include <QCloseEvent>
#include <QFileDialog>

DrawingWindow::DrawingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawingWindow)
{
    ui->setupUi(this);

    scribblearea = new ScribbleArea;
    setCentralWidget(scribblearea);

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
            scribblearea->openImage(filename);
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

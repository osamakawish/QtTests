#include "drawingwindow.h"
#include "ui_drawingwindow.h"

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

DrawingWindow::~DrawingWindow()
{
    delete ui;
}

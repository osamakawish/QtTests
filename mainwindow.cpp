#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    number = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QLabel *numberLabel = findChild<QLabel *>("number");
    number++;
    numberLabel->setNum(number);
}

void MainWindow::on_drawingWindowBtn_clicked()
{
    DrawingForm* drawingForm = new DrawingForm();
    drawingForm->show(); // necessary line: opens the window.
}

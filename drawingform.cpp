#include "drawingform.h"
#include "ui_drawingform.h"

DrawingForm::DrawingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawingForm)
{
    ui->setupUi(this);

    status = findChild<QLabel*>("status");
    pen = false;
}

DrawingForm::~DrawingForm()
{
    delete ui;
}

void DrawingForm::setLabelText()
{
    if (pen) {
        status->setText("Pen: On");
    } else {
        status->setText("Pen: Off");
    }
}

#ifndef DRAWINGFORM_H
#define DRAWINGFORM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class DrawingForm;
}

class DrawingForm : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingForm(QWidget *parent = nullptr);
    ~DrawingForm();

private:
    Ui::DrawingForm *ui;
    bool pen;
    QLabel* status;

    void setLabelText();
};

#endif // DRAWINGFORM_H

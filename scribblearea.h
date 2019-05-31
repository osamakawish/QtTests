#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QWidget>

namespace Ui {
class ScribbleArea;
}

class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    explicit ScribbleArea(QWidget *parent = nullptr);
    ~ScribbleArea();

private:
    Ui::ScribbleArea *ui;
};

#endif // SCRIBBLEAREA_H

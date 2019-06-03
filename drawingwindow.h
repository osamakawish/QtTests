#ifndef DRAWINGWINDOW_H
#define DRAWINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class DrawingWindow;
}

class DrawingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawingWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // File control: opening and saving files.
    void open();
    void save();

    // Pen properties.
    void penColor();
    void penWidth();

    // Not sure yet.
    void about();

private:
    Ui::DrawingWindow *ui;
};

#endif // DRAWINGWINDOW_H

#ifndef DRAWINGWINDOW_H
#define DRAWINGWINDOW_H

#include <QMainWindow>
#include "scribblearea.h"

namespace Ui {
class DrawingWindow;
}

class DrawingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawingWindow(QWidget *parent = nullptr);

protected:
    // Overriding to provide saving option.
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

    // Not sure about these methods purposes yet except saveFile.
    void createActions();
    void createMenus();
    // Checks for unsaved changes. Request to save file if true. False if cancelled.
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    // The scribble area.
    ScribbleArea *scribblearea;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif // DRAWINGWINDOW_H

#include "drawingwindow.h"
#include "ui_drawingwindow.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QImageWriter>

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

// Good example on how to connect slots and shortcuts to actions.
void DrawingWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    printAct = new QAction(tr("&Print..."), this);
    connect(printAct, SIGNAL(triggered()), scribbleArea, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            scribbleArea, SLOT(clearImage()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

// Useful for creating menus dynamically.
void DrawingWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool DrawingWindow::maybeSave()
{
    if (scribbleArea->isModified()) {
        // prompt save file dialog.
        QMessageBox::StandardButton ret;
        // Message box with save, discard, and cancel buttons.
        ret = QMessageBox::warning(this,tr("Scribble"),
                                   tr("This image has been modified. Do you want to save changes?"),
                                   QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);

        // Returns true if file is saved. False if cancelled.
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool DrawingWindow::saveFile(const QByteArray &fileFormat)
{
    QString basePath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this,tr("Save As"),
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                    .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                    .arg(QString::fromLatin1(fileFormat)));

    if (fileName.isEmpty()) {
        return scribbleArea->saveImage(fileName,fileFormat);
    } return false;
}



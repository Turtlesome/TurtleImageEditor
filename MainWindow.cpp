#include <QMainWindow>
#include "MainWindow.h"

MainWindow::MainWindow()
{
    this->setWindowTitle("TurtlePhotoEditor");
    this->resize(1920, 1080);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setAcceptDrops(true);
}


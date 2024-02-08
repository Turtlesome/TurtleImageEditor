#include <QApplication>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QMenu>
#include <QInputDialog>

#include "MainWindow.h"
#include "Image.h"



int main(int argc, char* argv[])
{
    QString fileName;
    QApplication app(argc, argv);
    QPixmap originalPixmap;
    MainWindow window;
    QLabel label(&window);
    Image* image = new Image(&label);


    QMenuBar* menuBar = new QMenuBar;
    window.setMenuBar(menuBar);

    QMenu* fileMenu = new QMenu("File");
    QMenu* optionMenu = new QMenu("Options");
	QMenu* otherMenu = new QMenu("Other");
    QMenu* zoomMenu = new QMenu("Zoom options");
	QMenu* helpMenu = new QMenu("Help");
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(optionMenu);
	menuBar->addMenu(otherMenu);
    menuBar->addMenu(zoomMenu);
    menuBar->addMenu(helpMenu);


    QAction* openAction = new QAction("Open");
    fileMenu->addAction(openAction);

    QAction* clearAction = new QAction("Clear");
    fileMenu->addAction(clearAction);

    QAction* saveAction = new QAction("Save");
    fileMenu->addAction(saveAction);

    QAction* zoomInAction = new QAction("Zoom In");
    QAction* zoomOutAction = new QAction("Zoom Out");


    QAction* brightnessAction = new QAction("Brightness");
    optionMenu->addAction(brightnessAction);

    QAction* contrastAction = new QAction("Contrast");
    optionMenu->addAction(contrastAction);

    QAction* hueAction = new QAction("Hue");
    optionMenu->addAction(hueAction);

    QAction* mirrorAction = new QAction("Mirror");
    optionMenu->addAction(mirrorAction);

    QAction* resizeAction = new QAction("Resize");
    optionMenu->addAction(resizeAction);

    QAction* rgbAction = new QAction("RGB Sliders");
    optionMenu->addAction(rgbAction);

    QAction* rotateAction = new QAction("Rotate");
    optionMenu->addAction(rotateAction);

    QAction* saturationAction = new QAction("Saturation");
    optionMenu->addAction(saturationAction);


	QAction* grayscaleAction = new QAction("Grayscale");
	otherMenu->addAction(grayscaleAction);


    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(image);
    QWidget* widget = new QWidget;
    widget->setLayout(layout);
    window.setCentralWidget(widget);


    QObject::connect(openAction, &QAction::triggered, image, &Image::loadImage);
    QObject::connect(clearAction, &QAction::triggered, image, &Image::clearImage);
    QObject::connect(saveAction, &QAction::triggered, image, &Image::saveImage);
    QObject::connect(brightnessAction, &QAction::triggered, image, &Image::changeBrightness);
    QObject::connect(contrastAction, &QAction::triggered, image, &Image::changeContrast);
    QObject::connect(hueAction, &QAction::triggered, image, &Image::changeHue);
    QObject::connect(mirrorAction, &QAction::triggered, image, &Image::mirrorImage);
    QObject::connect(resizeAction, &QAction::triggered, image, &Image::resizeImage);
    QObject::connect(rotateAction, &QAction::triggered, image, &Image::rotateImage);
    QObject::connect(saturationAction, &QAction::triggered, image, &Image::changeSaturation);
    QObject::connect(grayscaleAction, &QAction::triggered, image, &Image::convertToGrayscale);


    window.show();

    return app.exec();
}


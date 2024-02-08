#pragma once

#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QString>
#include <QDebug> 
#include <QInputDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>

class Image : public QLabel {
    Q_OBJECT

private:
    QString fileName;
    QPixmap originalPixmap;
    bool isMirrored;
    int brightness;
	int contrast;

public:
    Image(QWidget* parent = nullptr);
    ~Image();
    void loadImage();
    void clearImage();
    void saveImage();
    void changeBrightness();
    void changeContrast();
	void mirrorImage();
    void resizeImage();
    void rotateImage();
    void changeHue();
	void changeSaturation();
    
    void convertToGrayscale();
};

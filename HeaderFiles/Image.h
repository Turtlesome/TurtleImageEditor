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
#include <QPainter>
#include <QMouseEvent>

class Image : public QLabel {
    Q_OBJECT

private:
    QString fileName;
    QPixmap originalPixmap;
    QRect cropArea;
    QPoint origin;
    bool isMirrored;
    int brightness;
    int contrast;
    bool isCropMode;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

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
    void changeRGB();
    void createNegative();
    void cropImage();
    void enableCropMode(bool);
};

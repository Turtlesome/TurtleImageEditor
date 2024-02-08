#include "Image.h"

Image::Image(QWidget* parent) : QLabel(parent), isMirrored(false), brightness(0), contrast(0)
{
    fileName = QString();
    originalPixmap = QPixmap();
    isMirrored = false;
}   

Image::~Image()
{
    // No explicit cleanup needed
}

void Image::loadImage()
{
    fileName = QFileDialog::getOpenFileName(nullptr, "Open Image File", "", "Images (*.png *.jpg)");

    if (!fileName.isEmpty())
    {
        QPixmap pixmap(fileName);
        if (pixmap.isNull())
        {
            qDebug() << "Failed to load image: " << fileName;
        }
        else
        {
            originalPixmap = pixmap;
            this->setPixmap(pixmap);                
            this->setAlignment(Qt::AlignCenter);
        }
    }
}

void Image::clearImage()
{
    clear();
}

void Image::saveImage()
{
    if (!originalPixmap.isNull())
    {
        QImage modifiedImage = originalPixmap.toImage();
        QString saveFileName = QFileDialog::getSaveFileName(this, "Save Image", QDir::homePath(), "Images (*.png *.jpg *.bmp)");

        if (!saveFileName.isEmpty())
        {
            if (modifiedImage.save(saveFileName))
            {
                qDebug() << "Image saved successfully.";
            }
            else
            {
                qDebug() << "Error: Failed to save the image.";
            }
        }
    }
    else
    {
        qDebug() << "No image to save.";
    }
};

void Image::changeBrightness()
{
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        if (image.isNull())
        {
            qDebug() << "Failed to load image: " << fileName;
        }
        else
        {
            bool ok;
            int brightness = QInputDialog::getInt(nullptr, "Change Brightness", "Enter brightness value:", 0, -255, 255, 1, &ok);
            if (!ok) return;

            for (int y = 0; y < image.height(); y++)
            {
                for (int x = 0; x < image.width(); x++)
                {
                    QColor color(image.pixel(x, y));

                    int newRed = qBound(0, color.red() + brightness, 255);
                    int newGreen = qBound(0, color.green() + brightness, 255);
                    int newBlue = qBound(0, color.blue() + brightness, 255);

                    color.setRed(newRed);
                    color.setGreen(newGreen);
                    color.setBlue(newBlue);

                    image.setPixelColor(x, y, color);
                }
            }

            QPixmap pixmap = QPixmap::fromImage(image);

            originalPixmap = pixmap;
            this->setPixmap(pixmap);
            this->setAlignment(Qt::AlignCenter);

            this->brightness = brightness;
        }
    }
}

void Image::changeContrast()
{
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        if (image.isNull())
        {
            qDebug() << "Failed to load image: " << fileName;
        }
        else
        {
            bool ok;
            double contrast = QInputDialog::getDouble(nullptr, "Change Contrast", "Enter contrast value:", 1.0, -10.0, 10.0, 2, &ok);
            if (!ok) return;

            for (int y = 0; y < image.height(); y++)
            {
                for (int x = 0; x < image.width(); x++)
                {
                    QColor color(image.pixel(x, y));

                    int newRed = qBound(0, static_cast<int>(contrast * (color.red() - 127) + 127), 255);
                    int newGreen = qBound(0, static_cast<int>(contrast * (color.green() - 127) + 127), 255);
                    int newBlue = qBound(0, static_cast<int>(contrast * (color.blue() - 127) + 127), 255);

                    color.setRed(newRed);
                    color.setGreen(newGreen);
                    color.setBlue(newBlue);

                    image.setPixelColor(x, y, color);
                }
            }

            QPixmap pixmap = QPixmap::fromImage(image);

            originalPixmap = pixmap;
            this->setPixmap(pixmap);
            this->setAlignment(Qt::AlignCenter);

            this->contrast = contrast;
        }
    }
}

void Image::mirrorImage()
{
    if (!originalPixmap.isNull()) {
        QImage image = originalPixmap.toImage();
        isMirrored = !isMirrored;
        image = image.mirrored(isMirrored, false);
        originalPixmap = QPixmap::fromImage(image);
        this->setPixmap(originalPixmap);
    }
 };

void Image::resizeImage()
{
        QDialog dialog(this);
        QFormLayout form(&dialog);

        QSpinBox* widthSpinBox = new QSpinBox(&dialog);
        widthSpinBox->setRange(1, 10000);
        widthSpinBox->setValue(originalPixmap.width());
        form.addRow("Width:", widthSpinBox);

        QSpinBox* heightSpinBox = new QSpinBox(&dialog);
        heightSpinBox->setRange(1, 10000);
        heightSpinBox->setValue(originalPixmap.height());
        form.addRow("Height:", heightSpinBox);

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);

        QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        if (dialog.exec() == QDialog::Accepted && !originalPixmap.isNull())
        {
            originalPixmap = originalPixmap.scaled(widthSpinBox->value(), heightSpinBox->value(), Qt::IgnoreAspectRatio);
            this->setPixmap(originalPixmap);
        }
};

void Image::rotateImage()
{
    bool ok;
    int angle = QInputDialog::getInt(this, "Rotate", "Angle:", 0, -360, 360, 1, &ok);
    
    if (ok && !originalPixmap.isNull())
    {
        QTransform transform;
        transform.rotate(angle);
        QPixmap rotatedPixmap = originalPixmap.transformed(transform, Qt::SmoothTransformation);
            
        originalPixmap = rotatedPixmap;
        this->setPixmap(rotatedPixmap);
    }
};

void Image::changeHue()
{
    bool ok;
    int hueShift = QInputDialog::getInt(this, "Adjust hue", "Hue Shift:", 0, -180, 180, 1, &ok);
    if (ok && !originalPixmap.isNull())
    {
        QImage image = originalPixmap.toImage();
        for (int y = 0; y < image.height(); ++y)
        {
            for (int x = 0; x < image.width(); ++x)
            {
                QColor color(image.pixel(x, y));
                int h, s, v, a;
                color.getHsv(&h, &s, &v, &a);
                h = (h + hueShift + 360) % 360;
                color.setHsv(h, s, v, a);
                image.setPixelColor(x, y, color);
            }
        }
        originalPixmap = QPixmap::fromImage(image);
        this->setPixmap(originalPixmap);
    }
};

void Image::changeSaturation()
{
    bool ok;
    int saturationShift = QInputDialog::getInt(this, "Adjust saturation", "Saturation Shift:", 0, -255, 255, 1, &ok);
    if (ok && !originalPixmap.isNull())
    {
        QImage image = originalPixmap.toImage();
        for (int y = 0; y < image.height(); ++y)
        {
            for (int x = 0; x < image.width(); ++x)
            {
                QColor color(image.pixel(x, y));
                int h, s, v, a;
                color.getHsv(&h, &s, &v, &a);
                s = qBound(0, s + saturationShift, 255);
                color.setHsv(h, s, v, a);
                image.setPixelColor(x, y, color);
            }
        }
        originalPixmap = QPixmap::fromImage(image);
        this->setPixmap(originalPixmap);
    }
}

void Image::convertToGrayscale()
{
    if (!originalPixmap.isNull())
    {
        QImage image = originalPixmap.toImage();
        for (int y = 0; y < image.height(); ++y)
        {
            for (int x = 0; x < image.width(); ++x)
            {
                QColor color(image.pixel(x, y));
                int gray = qGray(color.rgb());
                color.setRgb(gray, gray, gray);
                image.setPixelColor(x, y, color);
            }
        }
        originalPixmap = QPixmap::fromImage(image);
        this->setPixmap(originalPixmap);
    }
};

void Image::changeRGB()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QSpinBox* spinBoxR = new QSpinBox(&dialog);
    spinBoxR->setRange(-255, 255);
    form.addRow("Red Shift:", spinBoxR);

    QSpinBox* spinBoxG = new QSpinBox(&dialog);
    spinBoxG->setRange(-255, 255);
    form.addRow("Green Shift:", spinBoxG);

    QSpinBox* spinBoxB = new QSpinBox(&dialog);
    spinBoxB->setRange(-255, 255);
    form.addRow("Blue Shift:", spinBoxB);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted && !originalPixmap.isNull())
    {
        int deltaR = spinBoxR->value();
        int deltaG = spinBoxG->value();
        int deltaB = spinBoxB->value();

        QImage image = originalPixmap.toImage();
        for (int y = 0; y < image.height(); ++y)
        {
            for (int x = 0; x < image.width(); ++x)
            {
                QColor color(image.pixel(x, y));
                int r = color.red();
                int g = color.green();
                int b = color.blue();
                r = qMin(255, qMax(0, r + deltaR));
                g = qMin(255, qMax(0, g + deltaG));
                b = qMin(255, qMax(0, b + deltaB));
                color.setRgb(r, g, b);
                image.setPixelColor(x, y, color);
            }
        }
        originalPixmap = QPixmap::fromImage(image);
        this->setPixmap(originalPixmap);
    }
};




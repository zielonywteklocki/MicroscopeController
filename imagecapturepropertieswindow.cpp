#include "imagecapturepropertieswindow.h"
#include "ui_imagecapturepropertieswindow.h"

ImageCapturePropertiesWindow::ImageCapturePropertiesWindow(QWidget *parent, QImageCapture* imageCapturePtr)
    : QDialog(parent)
    , imageCapturePtr(imageCapturePtr)
    , ui(new Ui::ImageCapturePropertiesWindow)
{
    ui->setupUi(this);
    if(imageCapturePtr)
    {
        switch(imageCapturePtr->fileFormat())
        {
        case  QImageCapture::FileFormat::UnspecifiedFormat :
            ui->rdBtnFileFormatJPEG->setChecked(true);
            break;
        case  QImageCapture::FileFormat::JPEG :
            ui->rdBtnFileFormatJPEG->setChecked(true);
            break;
        case  QImageCapture::FileFormat::PNG :
            ui->rdBtnFileFormatPNG->setChecked(true);
            break;
        case  QImageCapture::FileFormat::WebP :
            ui->rdBtnFileFormatWEBP->setChecked(true);
            break;
        case  QImageCapture::FileFormat::Tiff :
            ui->rdBtnFileFormatTIFF->setChecked(true);
            break;
        }

        switch(imageCapturePtr->quality())
        {
        case QImageCapture::Quality::VeryLowQuality :
            ui->rdBtnImageQualityVLow->setChecked(true);
            break;
        case QImageCapture::Quality::LowQuality :
            ui->rdBtnImageQualityLow->setChecked(true);
            break;
        case QImageCapture::Quality::NormalQuality :
            ui->rdBtnImageQualityNormal->setChecked(true);
            break;
        case QImageCapture::Quality::HighQuality :
            ui->rdBtnImageQualityHigh->setChecked(true);
            break;
        case QImageCapture::Quality::VeryHighQuality :
            ui->rdBtnImageQualityVHigh->setChecked(true);
            break;
        }
    }
}

ImageCapturePropertiesWindow::~ImageCapturePropertiesWindow()
{
    delete ui;
}

void ImageCapturePropertiesWindow::on_pbCancel_clicked()
{
    ImageCapturePropertiesWindow::close();
}

void ImageCapturePropertiesWindow::on_pbSave_clicked()
{
    if(ui->rdBtnFileFormatJPEG->isChecked()) imageCapturePtr->setFileFormat(QImageCapture::JPEG);
    else if(ui->rdBtnFileFormatPNG->isChecked())  imageCapturePtr->setFileFormat(QImageCapture::PNG);
    else if(ui->rdBtnFileFormatWEBP->isChecked()) imageCapturePtr->setFileFormat(QImageCapture::WebP);
    else if(ui->rdBtnFileFormatTIFF->isChecked()) imageCapturePtr->setFileFormat(QImageCapture::Tiff);

    if(ui->rdBtnImageQualityVLow->isChecked()) imageCapturePtr->setQuality(QImageCapture::VeryLowQuality);
    else if(ui->rdBtnImageQualityLow->isChecked()) imageCapturePtr->setQuality(QImageCapture::LowQuality);
    else if(ui->rdBtnImageQualityNormal->isChecked()) imageCapturePtr->setQuality(QImageCapture::NormalQuality);
    else if(ui->rdBtnImageQualityHigh->isChecked()) imageCapturePtr->setQuality(QImageCapture::HighQuality);
    else if(ui->rdBtnImageQualityVHigh->isChecked()) imageCapturePtr->setQuality(QImageCapture::VeryHighQuality);

    if(ui->grpBoxImgSize16->isChecked())
    {
        if(ui->rdBtnImgSize16_640->isChecked()) imageCapturePtr->setResolution(QSize(640, 360));
        else if(ui->rdBtnImgSize16_1280->isChecked()) imageCapturePtr->setResolution(QSize(1280, 720));
        else if(ui->rdBtnImgSize16_1366->isChecked()) imageCapturePtr->setResolution(QSize(1366, 768));
        else if(ui->rdBtnImgSize16_1600->isChecked()) imageCapturePtr->setResolution(QSize(1600, 900));
        else if(ui->rdBtnImgSize16_1920->isChecked()) imageCapturePtr->setResolution(QSize(1920, 1080));
    }

    if(ui->grpBoxImgSize4->isChecked())
    {
        if(ui->rdBtnImgSize4_640->isChecked()) imageCapturePtr->setResolution(QSize(640, 480));
        else if(ui->rdBtnImgSize4_1024->isChecked()) imageCapturePtr->setResolution(QSize(1024, 768));
        else if(ui->rdBtnImgSize4_1440->isChecked()) imageCapturePtr->setResolution(QSize(1440, 1080));
        else if(ui->rdBtnImgSize4_1600->isChecked()) imageCapturePtr->setResolution(QSize(1600, 1200));
        else if(ui->rdBtnImgSize4_2048->isChecked()) imageCapturePtr->setResolution(QSize(2048, 1536));
    }
}


void ImageCapturePropertiesWindow::on_rdBtnSelect16_clicked()
{
    ui->grpBoxImgSize16->setEnabled(true);
    ui->grpBoxImgSize4->setEnabled(false);
}


void ImageCapturePropertiesWindow::on_rdBtnSelect4_clicked()
{
    ui->grpBoxImgSize4->setEnabled(true);
    ui->grpBoxImgSize16->setEnabled(false);
}


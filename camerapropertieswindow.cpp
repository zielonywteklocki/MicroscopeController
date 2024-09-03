#include "camerapropertieswindow.h"
#include "ui_camerapropertieswindow.h"

CameraPropertiesWindow::CameraPropertiesWindow(QWidget *parent, QVideoWidget* videoWid, QMediaCaptureSession* mcs, QCamera* cam)
    : QDialog(parent)
    , videoWidPtr(videoWid)
    , mediaCaptureSessionPtr(mcs)
    , cameraPtr(cam)
    , ui(new Ui::CameraPropertiesWindow)
{
    ui->setupUi(this);
    getCameras();
}

CameraPropertiesWindow::~CameraPropertiesWindow()
{
    delete ui;
}

void CameraPropertiesWindow::getCameras()
{
    cameras = QMediaDevices::videoInputs();
    for( const QCameraDevice& camera : cameras)
    {
        ui->cbxCameras->addItem(camera.description());
    }
}

void CameraPropertiesWindow::on_pbStartCamera_clicked()
{
     startCamera();
}

void CameraPropertiesWindow::startCamera()
{
    cameraPtr->setCameraDevice(cameras.at(ui->cbxCameras->currentIndex()));
    cameraPtr->start();
    mediaCaptureSessionPtr->setCamera(cameraPtr);
    mediaCaptureSessionPtr->setVideoOutput(videoWidPtr);
}



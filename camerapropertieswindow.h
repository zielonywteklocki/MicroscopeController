#ifndef CAMERAPROPERTIESWINDOW_H
#define CAMERAPROPERTIESWINDOW_H

#include <QDialog>
#include <QCamera>
#include <QMediaDevices>
#include <QCameraDevice>
#include <QMediaCaptureSession>
#include <QVideoWidget>

namespace Ui {
class CameraPropertiesWindow;
}

class CameraPropertiesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CameraPropertiesWindow(QWidget *parent = nullptr, QVideoWidget* videoWid = nullptr,
                                    QMediaCaptureSession* mcs = nullptr, QCamera* cam = nullptr);
    ~CameraPropertiesWindow();

private slots:
    void on_pbStartCamera_clicked();

private:
    Ui::CameraPropertiesWindow *ui;

    QList<QCameraDevice> cameras;
    QMediaCaptureSession* mediaCaptureSessionPtr;
    QCamera* cameraPtr;
    QVideoWidget* videoWidPtr;

    void startCamera();
    void getCameras();
};

#endif // CAMERAPROPERTIESWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QCamera>
#include <QMediaDevices>
#include <QCameraDevice>
#include <QMediaCaptureSession>
#include <QVideoWidget>
#include <QImageCapture>
#include <QFileDialog>
#include <QDate>
#include <QTime>

#include <QDebug>
#include <QMessageBox>

#include <QSerialPort>
#include <QSerialPortInfo>

#include <QCommonStyle>
#include <QKeySequence>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

enum direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum moveSize{
    SMALL,
    MEDIUM,
    LARGE
};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVideoWidget _videoWid;

    QString MoveCommand(MainWindow::direction, MainWindow::moveSize);

    QList<QShortcut*> keyShortcuts;

    void updateStatusBarInfo();

private slots:

    void on_actionComPortProperties_triggered();
    void on_actionCameraProperties_triggered();
    void on_actionImage_Capture_Properties_triggered();
    void on_actionComPortSendMessage_triggered();


    void on_pbUpS_clicked();
    void on_pbUpM_clicked();
    void on_pbUpL_clicked();

    void on_pbDownS_clicked();
    void on_pbDownM_clicked();
    void on_pbDownL_clicked();

    void on_pbRightS_clicked();
    void on_pbRightM_clicked();
    void on_pbRightL_clicked();

    void on_pbLeftS_clicked();
    void on_pbLeftM_clicked();
    void on_pbLeftL_clicked();

    void on_pbCaptureImage_clicked();

private:
    Ui::MainWindow *ui;

    QSerialPort* serialPortPtr;
    QSerialPortInfo* serialPortInfoPtr;

    QMediaCaptureSession* mediaCaptureSessionPtr;
    QCamera* cameraPtr;
    QVideoWidget* videoWidPtr;
    QImageCapture* imageCapturePtr;

};
#endif // MAINWINDOW_H

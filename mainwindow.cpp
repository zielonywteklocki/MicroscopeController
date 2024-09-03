#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "comportpropertieswindow.h"
#include "camerapropertieswindow.h"
#include "imageCapturePropertiesWindow.h"
#include "comportsendmessagewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialPortPtr = new QSerialPort;
    serialPortInfoPtr = new QSerialPortInfo;
    mediaCaptureSessionPtr = new QMediaCaptureSession;
    cameraPtr = new QCamera;
    imageCapturePtr = new QImageCapture;
    mediaCaptureSessionPtr->setImageCapture(imageCapturePtr);
    videoWidPtr = ui->wVideo;

    QCommonStyle style;
    ui->pbUpS->setIcon(style.standardIcon(QStyle::SP_ArrowUp));
    ui->pbUpM->setIcon(style.standardIcon(QStyle::SP_ArrowUp));
    ui->pbUpL->setIcon(style.standardIcon(QStyle::SP_ArrowUp));
    ui->pbDownS->setIcon(style.standardIcon(QStyle::SP_ArrowDown));
    ui->pbDownM->setIcon(style.standardIcon(QStyle::SP_ArrowDown));
    ui->pbDownL->setIcon(style.standardIcon(QStyle::SP_ArrowDown));
    ui->pbLeftS->setIcon(style.standardIcon(QStyle::SP_ArrowLeft));
    ui->pbLeftM->setIcon(style.standardIcon(QStyle::SP_ArrowLeft));
    ui->pbLeftL->setIcon(style.standardIcon(QStyle::SP_ArrowLeft));
    ui->pbRightS->setIcon(style.standardIcon(QStyle::SP_ArrowRight ));
    ui->pbRightM->setIcon(style.standardIcon(QStyle::SP_ArrowRight ));
    ui->pbRightL->setIcon(style.standardIcon(QStyle::SP_ArrowRight ));

    keyShortcuts.push_back(new QShortcut(QKeySequence("W"), this));
    keyShortcuts.push_back(new QShortcut(QKeySequence("S"), this));
    keyShortcuts.push_back(new QShortcut(QKeySequence("A"), this));
    keyShortcuts.push_back(new QShortcut(QKeySequence("D"), this));

    keyShortcuts.push_back(new QShortcut(QKeySequence("Ctrl+W"), this));
    keyShortcuts.push_back(new QShortcut(QKeySequence("Ctrl+S"), this));
    keyShortcuts.push_back(new QShortcut(QKeySequence("Ctrl+A"), this));
    keyShortcuts.push_back(new QShortcut(QKeySequence("Ctrl+D"), this));

    keyShortcuts.push_back(new QShortcut(QKeySequence("Shift+W"), this));
    keyShortcuts.push_back(new QShortcut(QKeySequence("Shift+S"), this));
    keyShortcuts.push_back(new QShortcut(QKeySequence("Shift+A"), this));
    keyShortcuts.push_back(new QShortcut(QKeySequence("Shift+D"), this));

    QObject::connect(keyShortcuts.at(0), &QShortcut::activated, this, &MainWindow::on_pbUpS_clicked);
    QObject::connect(keyShortcuts.at(1), &QShortcut::activated, this, &MainWindow::on_pbDownS_clicked);
    QObject::connect(keyShortcuts.at(2), &QShortcut::activated, this, &MainWindow::on_pbLeftS_clicked);
    QObject::connect(keyShortcuts.at(3), &QShortcut::activated, this, &MainWindow::on_pbRightS_clicked);

    QObject::connect(keyShortcuts.at(4), &QShortcut::activated, this, &MainWindow::on_pbUpM_clicked);
    QObject::connect(keyShortcuts.at(5), &QShortcut::activated, this, &MainWindow::on_pbDownM_clicked);
    QObject::connect(keyShortcuts.at(6), &QShortcut::activated, this, &MainWindow::on_pbLeftM_clicked);
    QObject::connect(keyShortcuts.at(7), &QShortcut::activated, this, &MainWindow::on_pbRightM_clicked);

    QObject::connect(keyShortcuts.at(8), &QShortcut::activated, this, &MainWindow::on_pbUpL_clicked);
    QObject::connect(keyShortcuts.at(9), &QShortcut::activated, this, &MainWindow::on_pbDownL_clicked);
    QObject::connect(keyShortcuts.at(10), &QShortcut::activated, this, &MainWindow::on_pbLeftL_clicked);
    QObject::connect(keyShortcuts.at(11), &QShortcut::activated, this, &MainWindow::on_pbRightL_clicked);

   // QObject::connect(serialPortPtr->baudRateChanged(),  this, &MainWindow::updateStatusBarInfo)
}

MainWindow::~MainWindow()
{
    delete ui;

    if(serialPortPtr != nullptr)
    {
        serialPortPtr->close();
        delete serialPortPtr;
    }

    if(serialPortInfoPtr != nullptr)
    {
        delete serialPortInfoPtr;
    }
}

void MainWindow::on_actionComPortProperties_triggered()
{
    ComPortPropertiesWindow comPortPropertiesWindow(this, serialPortPtr);
    comPortPropertiesWindow.setModal(true);
    comPortPropertiesWindow.exec();
}

void MainWindow::on_actionComPortSendMessage_triggered(){
    ComPortSendMessageWindow comPortSendMessageWindow(this);
    comPortSendMessageWindow.setModal(true);
    comPortSendMessageWindow.exec();
}

void MainWindow::on_actionCameraProperties_triggered()
{
    CameraPropertiesWindow cameraPropertiesWindow(this, videoWidPtr, mediaCaptureSessionPtr, cameraPtr);
    cameraPropertiesWindow.setModal(false);
    cameraPropertiesWindow.exec();
}

void MainWindow::on_actionImage_Capture_Properties_triggered()
{
    ImageCapturePropertiesWindow imageCapturePropertiesWindow(this, imageCapturePtr);
    imageCapturePropertiesWindow.setModal(true);
    imageCapturePropertiesWindow.exec();
}

QString MainWindow::MoveCommand(MainWindow::direction dir, MainWindow::moveSize size)
{
    QString ret("G1 ");
    switch(dir)
    {
        case MainWindow::direction::UP :
            ret += "X ";
            break;
        case MainWindow::direction::DOWN :
            ret += "X -";
            break;
        case MainWindow::direction::RIGHT :
            ret += "Y ";
            break;
        case MainWindow::direction::LEFT :
            ret += "Y -";
            break;
    }
    switch(size)
    {
        case MainWindow::moveSize::SMALL :
            ret += "0.1 ";
            break;
        case MainWindow::moveSize::MEDIUM :
            ret += "0.4 ";
            break;
        case MainWindow::moveSize::LARGE :
            ret += "1.6 ";
            break;
    }

    ret += "F50\n";

    return ret;
}

void MainWindow::on_pbUpS_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::UP, MainWindow::moveSize::SMALL).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void MainWindow::on_pbUpM_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::UP, MainWindow::moveSize::MEDIUM).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void MainWindow::on_pbUpL_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::UP, MainWindow::moveSize::LARGE).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void MainWindow::on_pbDownS_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::DOWN, MainWindow::moveSize::SMALL).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void MainWindow::on_pbDownM_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::DOWN, MainWindow::moveSize::MEDIUM).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void MainWindow::on_pbDownL_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::DOWN, MainWindow::moveSize::LARGE).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void  MainWindow::on_pbRightS_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::RIGHT, MainWindow::moveSize::SMALL).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void  MainWindow::on_pbRightM_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::RIGHT, MainWindow::moveSize::MEDIUM).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void  MainWindow::on_pbRightL_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::RIGHT, MainWindow::moveSize::LARGE).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void  MainWindow::on_pbLeftS_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::LEFT, MainWindow::moveSize::SMALL).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void  MainWindow::on_pbLeftM_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::LEFT, MainWindow::moveSize::MEDIUM).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void  MainWindow::on_pbLeftL_clicked()
{
    if(-1 == serialPortPtr->write(MoveCommand(MainWindow::direction::LEFT, MainWindow::moveSize::LARGE).toLatin1() ) )
    {
        QMessageBox::warning(this, "Error", "Write function returned -1");
    }
}

void MainWindow::on_pbCaptureImage_clicked()
{
    QDate currentDate = QDate::currentDate();
    QTime currentTime = QTime::currentTime();
    QString fileName = "C:\\Users\\Adam\\Desktop\\ImageCaptures\\Img_" + currentDate.toString("yyyy-MM-dd") + "_" + currentTime.toString("HH-mm-ss");
    QString filedir = QFileDialog::getSaveFileName(this, "Save Image", fileName);
    if (!filedir.isEmpty()) {
        imageCapturePtr->captureToFile(filedir);
    }
}

void MainWindow::updateStatusBarInfo()
{
    QString message = "COM: ";
    if(serialPortPtr)
    {
        if(serialPortPtr->isOpen())
        {
            message += serialPortPtr->portName() + " ";
            message += QString::number(serialPortPtr->baudRate()) + " ";
            message += QString::number(serialPortPtr->dataBits()) + "," + QString::number(serialPortPtr->parity()) + "," + QString::number(serialPortPtr->stopBits()) + ", ";
        }
    }
    else
        message += "NONE, ";

    message += "CAMERA: ";

    if(cameraPtr)
    {
        if(cameraPtr->isActive())
        {
            message += cameraPtr->cameraDevice().description() + " ";
        }
    }
    else
        message += "NONE, ";

    if(cameraPtr)
    {
        if(cameraPtr->isAvailable())
        {
            message += cameraPtr->cameraDevice().description() + " ";
        }
    }
    else
        message += "NONE, ";

    ui->statusbar->showMessage(message);
}


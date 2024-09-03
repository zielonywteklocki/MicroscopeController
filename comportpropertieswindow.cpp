#include "comportpropertieswindow.h"
#include "ui_comportpropertieswindow.h"
#include "mainwindow.h"

ComPortPropertiesWindow::ComPortPropertiesWindow(QWidget* parent,
                                                QSerialPort* serialPort)
    : QDialog(parent)
    , serialPortPtr(serialPort)
    , ui(new Ui::ComPortPropertiesWindow)
{
    ui->setupUi(this);
    foreach(auto& port, QSerialPortInfo::availablePorts())
    {
        ui->cbxPortName->addItem( port.portName() );
    }
    if(serialPortPtr != nullptr)
    {
        ui->cbxPortName->setCurrentText(serialPortPtr->portName());
    }

    for(const auto& baud : baudRatesList)
    {
        ui->cbxBaud->addItem( QString::number(baud.baudRate) );
        ui->cbxBaud->setCurrentIndex(7);
    }


    for(const auto& dataBits : dataBitsList)
    {
        ui->cbxDataBits->addItem( QString::number(dataBits.dataBits) );
        ui->cbxDataBits->setCurrentIndex(3);
    }

    for(const auto& parity : paritiesList)
    {
        ui->cbxParity->addItem( parity.parity );
        ui->cbxParity->setCurrentIndex(0);
    }

    for(const auto& stopBits : stopBitsList)
    {
        ui->cbxStopBits->addItem( stopBits.stopBits );
        ui->cbxStopBits->setCurrentIndex(0);
    }
}

ComPortPropertiesWindow::~ComPortPropertiesWindow()
{
    delete ui;
}

void ComPortPropertiesWindow::on_pbConnect_clicked()
{
    serialPortPtr->setPortName(ui->cbxPortName->currentText());
    serialPortPtr->setBaudRate(baudRatesList.at(ui->cbxBaud->currentIndex()).eBaudRate);

    serialPortPtr->setDataBits(dataBitsList.at(ui->cbxDataBits->currentIndex()).eDataBits);

    serialPortPtr->setParity(paritiesList.at(ui->cbxParity->currentIndex()).eParity);

    serialPortPtr->setStopBits(stopBitsList.at(ui->cbxStopBits->currentIndex()).eStopBits);

    if(serialPortPtr->open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this, "Result", "Port opened successfully");
    }
    else
    {
        QMessageBox::critical(this, "Port Error", "Unable to open specific port");
    }

    MainWindow* mainWindow = qobject_cast<MainWindow*>(parentWidget());
    if (mainWindow) {
        // Update the status bar of the parent window
        mainWindow->updateStatusBarInfo();
    }
}

void ComPortPropertiesWindow::on_pbCancel_clicked()
{
    ComPortPropertiesWindow::close();
}


void ComPortPropertiesWindow::on_pbDisconnect_clicked()
{
    if(serialPortPtr != nullptr)
        if(serialPortPtr->isOpen())
        {
            serialPortPtr->close();
            QMessageBox::information(this, "Result", "Port closed successfully");
            return;
        }

    QMessageBox::critical(this, "Result", "Port was not disconneted");
}


void ComPortPropertiesWindow::on_pbRelativeMove_clicked()
{
    if(serialPortPtr != nullptr)
        if(serialPortPtr->isOpen())
        {
            serialPortPtr->write("G91\n");
            QMessageBox::information(this, "Result", "Relative move set");
            return;
        }

    QMessageBox::critical(this, "Result", "Something went wrong");
}


void ComPortPropertiesWindow::on_pbAbsoluteMove_clicked()
{
    if(serialPortPtr != nullptr)
        if(serialPortPtr->isOpen())
        {
            serialPortPtr->write("G90\n");
            QMessageBox::information(this, "Result", "Absolute move set");
            return;
        }

    QMessageBox::critical(this, "Result", "Something went wrong");
}

void ComPortPropertiesWindow::on_pbSetAsOrigin_clicked()
{
    if(serialPortPtr != nullptr)
        if(serialPortPtr->isOpen())
        {
            serialPortPtr->write("G92\n");
            QMessageBox::information(this, "Result", "Origin set to current point");
            return;
        }

    QMessageBox::critical(this, "Result", "Something went wrong");
}


void ComPortPropertiesWindow::on_pbUnits_mm_clicked()
{
    if(serialPortPtr != nullptr)
        if(serialPortPtr->isOpen())
        {
            serialPortPtr->write("G21\n");
            QMessageBox::information(this, "Result", "Units set to mm");
            return;
        }

    QMessageBox::critical(this, "Result", "Something went wrong");
}


void ComPortPropertiesWindow::on_pbUnits_in_clicked()
{
    if(serialPortPtr != nullptr)
        if(serialPortPtr->isOpen())
        {
            serialPortPtr->write("G20\n");
            QMessageBox::information(this, "Result", "Units set to inches");
            return;
        }

    QMessageBox::critical(this, "Result", "Something went wrong");
}


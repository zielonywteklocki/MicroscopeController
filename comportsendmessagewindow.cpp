#include "comportsendmessagewindow.h"
#include "ui_comportsendmessagewindow.h"

ComPortSendMessageWindow::ComPortSendMessageWindow(QWidget *parent, QSerialPort* serialPort)
    : QDialog(parent)
    , serialPortPtr(serialPort)
    , ui(new Ui::ComPortSendMessageWindow)
{
    ui->setupUi(this);
    connect(serialPort, &QSerialPort::readyRead, this, &ComPortSendMessageWindow::readSerialData);
}

ComPortSendMessageWindow::~ComPortSendMessageWindow()
{
    delete ui;
}

void ComPortSendMessageWindow::on_pbClearScreen_clicked()
{
    ui->tEMessagesReceived->clear();
}


void ComPortSendMessageWindow::on_pbSendMessage_clicked()
{
    QString message = ui->leMessageToSend->text();
    if(ui->cbCarriageReturn->isChecked())
        message += "\r";
    if(ui->cbNewLine->isChecked())
        message += "\n";

    if(serialPortPtr)
    {
        if(serialPortPtr->isOpen())
        {
            serialPortPtr->write(message.toLatin1());
        }
        else
        {
            QMessageBox::critical(this, "ERROR", "Port is closed");
        }
    } else {
        QMessageBox::critical(this, "ERROR", "Pointer to QSerialClass is nullptr");
    }
}

void ComPortSendMessageWindow::readSerialData()
{
    QByteArray data = serialPortPtr->readAll();
    ui->tEMessagesReceived->append(data);
}


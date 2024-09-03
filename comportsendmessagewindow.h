#ifndef COMPORTSENDMESSAGEWINDOW_H
#define COMPORTSENDMESSAGEWINDOW_H

#include <QDialog>
#include <QSerialPort>
#include <QMessageBox>

namespace Ui {
class ComPortSendMessageWindow;
}

class ComPortSendMessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ComPortSendMessageWindow(QWidget *parent = nullptr, QSerialPort* serialPort = nullptr);
    ~ComPortSendMessageWindow();

private slots:
    void on_pbClearScreen_clicked();

    void on_pbSendMessage_clicked();

    void readSerialData();

private:
    Ui::ComPortSendMessageWindow *ui;
    QSerialPort* serialPortPtr;
};

#endif // COMPORTSENDMESSAGEWINDOW_H

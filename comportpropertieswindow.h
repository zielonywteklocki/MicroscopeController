#ifndef COMPORTPROPERTIESWINDOW_H
#define COMPORTPROPERTIESWINDOW_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QMessageBox>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui {
class ComPortPropertiesWindow;
struct BaudRates;
struct Parity;
struct StopBits;
}
QT_END_NAMESPACE

struct BaudRates
{
    quint8 index;
    quint32 baudRate;
    QSerialPort::BaudRate eBaudRate;
};

struct DataBits
{
    quint8 index;
    quint8 dataBits;
    QSerialPort::DataBits eDataBits;
};

struct Parity
{
    quint8 index;
    QString parity;
    QSerialPort::Parity eParity;
};

struct StopBits
{
    quint8 index;
    QString stopBits;
    QSerialPort::StopBits eStopBits;
};

class ComPortPropertiesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ComPortPropertiesWindow(QWidget* parent = nullptr, QSerialPort* serialPort = nullptr);
    ~ComPortPropertiesWindow();

    const QList<BaudRates> baudRatesList{{0, 1200, QSerialPort::Baud1200},
                                        {1, 2400, QSerialPort::Baud2400},
                                        {2, 4800, QSerialPort::Baud4800},
                                        {3, 9600, QSerialPort::Baud9600},
                                        {4, 19200, QSerialPort::Baud19200},
                                        {5, 38400, QSerialPort::Baud38400},
                                        {6, 57600, QSerialPort::Baud57600},
                                        {7, 115200, QSerialPort::Baud115200} };

    const QList<DataBits> dataBitsList{ {0, 5, QSerialPort::Data5},
                                        {1, 6, QSerialPort::Data6},
                                        {2, 7, QSerialPort::Data7},
                                        {3, 8, QSerialPort::Data8}  };

    const QList<Parity> paritiesList{   {0, "No",   QSerialPort::NoParity},
                                        {1, "Odd",  QSerialPort::OddParity},
                                        {2, "Even", QSerialPort::EvenParity},
                                        {3, "Space",QSerialPort::SpaceParity},
                                        {4, "Mark", QSerialPort::MarkParity}};

    const QList<StopBits> stopBitsList{ {0, "One",        QSerialPort::OneStop },
                                        {1, "OneAndHalf", QSerialPort::OneAndHalfStop},
                                        {2, "Two",        QSerialPort::TwoStop}};

private slots:
    void on_pbCancel_clicked();
    void on_pbConnect_clicked();
    void on_pbDisconnect_clicked();
    void on_pbRelativeMove_clicked();
    void on_pbAbsoluteMove_clicked();
    void on_pbSetAsOrigin_clicked();
    void on_pbUnits_mm_clicked();
    void on_pbUnits_in_clicked();

private:
    Ui::ComPortPropertiesWindow *ui;
    QSerialPort* serialPortPtr;
};

#endif // COMPORTPROPERTIESWINDOW_H

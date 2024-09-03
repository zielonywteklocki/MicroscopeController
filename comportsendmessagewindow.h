#ifndef COMPORTSENDMESSAGEWINDOW_H
#define COMPORTSENDMESSAGEWINDOW_H

#include <QDialog>

namespace Ui {
class ComPortSendMessageWindow;
}

class ComPortSendMessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ComPortSendMessageWindow(QWidget *parent = nullptr);
    ~ComPortSendMessageWindow();

private:
    Ui::ComPortSendMessageWindow *ui;
};

#endif // COMPORTSENDMESSAGEWINDOW_H

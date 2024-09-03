#include "comportsendmessagewindow.h"
#include "ui_comportsendmessagewindow.h"

ComPortSendMessageWindow::ComPortSendMessageWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ComPortSendMessageWindow)
{
    ui->setupUi(this);
}

ComPortSendMessageWindow::~ComPortSendMessageWindow()
{
    delete ui;
}

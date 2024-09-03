#ifndef IMAGECAPTUREPROPERTIESWINDOW_H
#define IMAGECAPTUREPROPERTIESWINDOW_H

#include <QDialog>
#include <QImageCapture>

namespace Ui {
class ImageCapturePropertiesWindow;
}

class ImageCapturePropertiesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ImageCapturePropertiesWindow(QWidget *parent = nullptr, QImageCapture* imageCapturePtr = nullptr);
    ~ImageCapturePropertiesWindow();

private slots:

    void on_pbCancel_clicked();

    void on_pbSave_clicked();

    void on_rdBtnSelect16_clicked();

    void on_rdBtnSelect4_clicked();

private:
    Ui::ImageCapturePropertiesWindow *ui;
    QImageCapture* imageCapturePtr;
};

#endif // IMAGECAPTUREPROPERTIESWINDOW_H

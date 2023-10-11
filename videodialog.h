#ifndef VIDEODIALOG_H
#define VIDEODIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QVideoWidget>

namespace Ui {
class VideoDialog;
}

class VideoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VideoDialog(QWidget *parent = nullptr);
    ~VideoDialog();

private slots:
    void on_pushButton_clicked();

    void on_zoom_btn_clicked();

private:
    Ui::VideoDialog *ui;
    QMediaPlayer* player;
    QVideoWidget* videoWigdet;
    QNetworkRequest request;
};

#endif // VIDEODIALOG_H

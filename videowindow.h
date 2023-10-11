#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
namespace Ui {
class VideoWindow;
}

class VideoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit VideoWindow(QWidget *parent = nullptr);
    ~VideoWindow();

private:
    Ui::VideoWindow *ui;
    QMediaPlayer* player;
    QVideoWidget* videoWidget;
};

#endif // VIDEOWINDOW_H

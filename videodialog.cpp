#include "videodialog.h"
#include "ui_videodialog.h"
#include "hikvision.cpp"

VideoDialog::VideoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoDialog)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    videoWigdet = new QVideoWidget(this);
    player->setVideoOutput(ui->videoView);
    player->setMedia(QUrl(rtspLink()));
    player->play();
}

int zoomButtonState = 0;

VideoDialog::~VideoDialog()
{
    delete ui;
}

void VideoDialog::on_pushButton_clicked()
{
   doNuc();
}

void VideoDialog::on_zoom_btn_clicked()
{
    switch (zoomButtonState){
        case 0:
            makeZoom(1);
            break;
        case 1:
            makeZoom(2);
            break;
        case 2:
            makeZoom(3);
            break;
        case 3:
            makeZoom(4);
            break;
      }

    zoomButtonState ++;

    if(zoomButtonState > 4){
        zoomButtonState = 0;

    }
}


#include "incorrect.h"
#include "ui_incorrect.h"

#include "bg.h"
#include "en.h"

#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QTouchEvent>

Incorrect::Incorrect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Incorrect)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    //QCursor cursor(Qt::BlankCursor);
    //QApplication::setOverrideCursor(cursor);
    //QApplication::changeOverrideCursor(cursor);

    setAttribute(Qt::WA_AcceptTouchEvents, true);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    //this->move(485, 280);
    this->move(x, y);

    //setAttribute(Qt::WA_AcceptTouchEvents, true);

    onShakeWindow();
}
Incorrect::~Incorrect()
{
    delete ui;
}

void Incorrect::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F6) //ok
    {
        hideWindow();
    }
}

void Incorrect::switchToBG()
{
    ui->label->setText(lblWrongPassTxt_BG);
    ui->label->adjustSize();
    ui->label->setGeometry(
                (this->width() - ui->label->width())/2,
                ui->label->geometry().y(),
                ui->label->width(),
                ui->label->height());
}

void Incorrect::switchToEN()
{
    ui->label->setText(lblWrongPassTxt_EN);
    ui->label->adjustSize();
    ui->label->setGeometry(
                (this->width() - ui->label->width())/2,
                ui->label->geometry().y(),
                ui->label->width(),
                ui->label->height());
}

void Incorrect::hideWindow()
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "pos");

    pAnimation->setDuration(200);

    pAnimation->setLoopCount(1);

    pAnimation->setKeyValueAt(0, QPoint(geometry().x(), geometry().y()));

    pAnimation->setKeyValueAt(1, QPoint(geometry().x(), 1200));

    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(pAnimation, SIGNAL(finished()), this, SLOT(close()));
}

void Incorrect::on_btnOk_pressed()
{
    hideWindow();
}

void Incorrect::onShakeWindow()
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "pos");

    pAnimation->setDuration(500);

    pAnimation->setLoopCount(1);

    pAnimation->setKeyValueAt(0, QPoint(geometry().x() - 10, geometry().y() - 10));

    pAnimation->setKeyValueAt(0.1, QPoint(geometry().x() + 6, geometry().y() + 6));

    pAnimation->setKeyValueAt(0.2, QPoint(geometry().x() - 6, geometry().y() + 6));

    pAnimation->setKeyValueAt(0.3, QPoint(geometry().x() + 6, geometry().y() - 6));

    pAnimation->setKeyValueAt(0.4, QPoint(geometry().x() - 6, geometry().y() - 6));

    pAnimation->setKeyValueAt(0.5, QPoint(geometry().x() + 6, geometry().y() + 6));

    pAnimation->setKeyValueAt(0.6, QPoint(geometry().x() - 6, geometry().y() + 6));

    pAnimation->setKeyValueAt(0.7, QPoint(geometry().x() + 6, geometry().y() - 6));

    pAnimation->setKeyValueAt(0.8, QPoint(geometry().x() - 6, geometry().y() - 6));

    pAnimation->setKeyValueAt(0.9, QPoint(geometry().x() + 6, geometry().y() + 6));

    pAnimation->setKeyValueAt(1, QPoint(geometry().x() + 2, geometry().y() + 2));

    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Incorrect::gpioBtnOk()
{
    hideWindow();
}

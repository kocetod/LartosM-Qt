#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QDialog>
#include<QTouchEvent>
#include "SaveLartosUserData.h"

namespace Ui {
class Language;
}

class Language : public QDialog
{
    Q_OBJECT

public:
    explicit Language(QWidget *parent = nullptr);
    ~Language();


public slots:

    void on_btnBG_released();

    void on_btnEN_released();

    void gpioBtnOk();

    void gpioBtnLeft();

    void gpioBtnRight();

public:
    Ui::Language *ui;
    SaveLartosUserData saveUserData;
};

#endif // LANGUAGE_H

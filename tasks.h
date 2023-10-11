#ifndef TASKS_H
#define TASKS_H

#include "expanded.h"

#include <QDialog>

namespace Ui {
class Tasks;
}

class Tasks : public QDialog
{
    Q_OBJECT

public:
    explicit Tasks(QWidget *parent = nullptr);
    ~Tasks();

    void switchToBG();

    void switchToEN();

    void gpioBtnOk();

    void gpioBtnLeft();

    void gpioBtnRight();

    void gpioBtnUp();

    void gpioBtnDown();

private slots:
    void task1a_pressed();
    void task1b_pressed();
    void task1c_pressed();
    void task2_pressed();
    void task3_pressed();
    void btnBack_pressed();
    void task1a_released();
    void task1b_released();
    void task1c_released();
    void task2_released();
    void task3_released();
    void btnBack_released();
    void btnConfirm_pressed();
    void btnConfirm_released();

    void on_task1A_pressed();

    void on_task1B_pressed();

    void on_task1C_pressed();

    void on_task2_pressed();

    void on_task3_pressed();

    void on_btnConfirm_pressed();

    void on_btnBack_pressed();

    void on_btnBack_released();

private:
    Ui::Tasks *ui;
    Expanded *ex;
};

#endif // TASKS_H

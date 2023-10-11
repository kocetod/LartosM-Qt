#ifndef INCORRECT_H
#define INCORRECT_H

#include <QDialog>

namespace Ui {
class Incorrect;
}

class Incorrect : public QDialog
{
    Q_OBJECT

public:
    explicit Incorrect(QWidget *parent = nullptr);
    ~Incorrect();

    void switchToBG();

    void switchToEN();

    void gpioBtnOk();

private slots:

    void on_btnOk_pressed();

    void onShakeWindow();

    void hideWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Incorrect *ui;
};

#endif // INCORRECT_H

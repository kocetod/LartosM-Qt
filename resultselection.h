#ifndef RESULTSELECTION_H
#define RESULTSELECTION_H

#include <QDialog>
#include <QStandardItemModel>
#include "LartosPointObj.h"
#include "SaveLartosPoints.h"

namespace Ui {
class ResultSelection;
}

class ResultSelection : public QDialog
{
    Q_OBJECT

public:
    explicit ResultSelection(QWidget *parent = nullptr);
    ~ResultSelection();

    void showTaskResult();

    void showDirAngleResult();

    void switchToBG();

    void switchToEN();

    void btnUse_pressed();

    void btnUse_released();

    void btnUse_selected();

    void btnNo_pressed();

    void btnNo_released();

    void btnNo_selected();

    void btnUseDirAngle_pressed();

    void btnUseDirAngle_released();

    void btnUseDirAngle_selected();

    void btnNo_2_pressed();

    void btnNo_2_released();

    void btnNo_2_selected();

    void btnChoose_pressed();

    void btnChoose_released();

    void btnChoose_selected();

    void btnClose_pressed();

    void btnClose_released();

    void gpioBtnOk();

    void gpioBtnLeft();

    void gpioBtnRight();

private slots:
    void on_btnUse_pressed();

    void on_btnUse_released();

    void on_btnNo_pressed();

    void on_btnNo_released();

    void on_btnChoose_pressed();

    void on_btnChoose_released();

    void on_point_listView_pressed(const QModelIndex &index);

    void on_pointA_pressed();

    void pointA_released();

    void on_pointB_pressed();

    void pointB_released();

    void on_pointC_pressed();

    void pointC_released();

    void on_pointD_pressed();

    void pointD_released();

    void on_btnClose_pressed();

    void on_btnClose_released();

    void on_btnUseDirAngle_pressed();

    void on_btnUseDirAngle_released();

    void on_btnNo_2_pressed();

    void on_btnNo_2_released();

private:
    Ui::ResultSelection *ui;

    void loadPointData();
    void showDataInTableView(LartosPointObj point);
    void initTableView();

    QStandardItemModel *model;
    QStringList horizontalHeader;
    QStringList verticalHeader;
    QHash<QString,LartosPointObj> hashPoint;
    SaveLartosPoint *savePointObj;

    QModelIndex pointIndex;
    QString txtLat;
    QString txtLong;
};

#endif // RESULTSELECTION_H

#include "resultselection.h"
#include "ui_resultselection.h"

#include "bg.h"
#include "en.h"

#include<QKeyEvent>
#include "variables.h"

extern "C"
{
#include "Periph/CompassDataManager.h"
#include "Application/SharedVariables.h"
}

QString currentX = "24.56754";
QString currentY = "28.54634";
QString currentH = "10.4";

QString newX = "23.65467";
QString newY = "27.97867";
QString newH = "10.3";

ResultSelection::ResultSelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultSelection)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_AcceptTouchEvents, true);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    hashPoint = savePointObj->readPointFromFile();

    ui->grBoxUpdatePosition->hide();
    ui->grBoxUpdateDirAngle->hide();
    ui->btnChoose->setFocus();
    ui->pointA->setEnabled(false);
    ui->pointB->setEnabled(false);
    ui->pointC->setEnabled(false);
    ui->pointD->setEnabled(false);

    if(task == 2)
    {
        ui->pointC->show();
        ui->pointD->show();
    }
    else if(task == 3)
    {
        ui->pointC->hide();
        ui->pointD->hide();
    }
    else if(task == 4)
    {
        ui->pointC->hide();
        ui->pointD->hide();
    }

    initTableView();
    loadPointData();
}

ResultSelection::~ResultSelection()
{
    delete ui;
}

void ResultSelection::showTaskResult()
{
    ui->lblCurrX->setText(txtLat + QString().setNum(X_parameter, 'g', 8));
    ui->lblCurrY->setText(txtLong + QString().setNum(Y_parameter, 'g', 8));
    ui->lblCurrH->setText("H: " + QString::number(H_parameter));
    ui->lblNewX->setText(txtLat + QString().setNum(newLat, 'g', 8));
    ui->lblNewY->setText(txtLong + QString().setNum(newLong, 'g', 8));
    ui->lblNewH->setText("H: " + newAlt);
    ui->grBoxPoints->hide();
    ui->grBoxUpdateDirAngle->hide();
    ui->grBoxUpdatePosition->setGeometry(0, 0, 870, 500);
    ui->grBoxUpdatePosition->show();
    ui->btnUse->setFocus();
}

void ResultSelection::showDirAngleResult()
{
    ui->lblCurrDirAngleValue->setText(QString::number((cdmHeading/1000)));
    ui->lblNewDirAngleValue->setText(QString::number(alfa_deg));
    ui->grBoxPoints->hide();
    ui->grBoxUpdatePosition->hide();
    ui->grBoxUpdateDirAngle->setGeometry(0, 0, 870, 500);
    ui->grBoxUpdateDirAngle->show();
}

void ResultSelection::loadPointData(){

  ui->point_listView->resizeColumnsToContents();
  ui->point_listView->resizeRowsToContents();
  int indexNew = 1;
  foreach (LartosPointObj val, hashPoint) {
      val.setLartosPointIndex(QString::number(indexNew)); 

      if(coordinate_type == "utm" && val.typeOfCoordinates == "UTM")
      {
          showDataInTableView(val);
      }
      else if(coordinate_type == "xy" && val.typeOfCoordinates == "X,Y")
      {
          showDataInTableView(val);
      }
      else if(coordinate_type == "bl" && val.typeOfCoordinates == "B,L")
      {
          showDataInTableView(val);
      }
      indexNew++;
    }
}

void ResultSelection::showDataInTableView(LartosPointObj point){

  QStandardItem *idCol = new QStandardItem(point.getLartosPointIndex());
  idCol->setEditable(false);
  QStandardItem *nameCol = new QStandardItem(point.getLartosPointName());
  QFont fontCol;
  fontCol.setBold(true);
  nameCol->setFont(fontCol);
  QStandardItem *latCol = new QStandardItem(point.getLartosPointLattitude());
  QStandardItem *longCol = new QStandardItem(point.getLartosPointLongitude());
  QStandardItem *atiCol = new QStandardItem(point.getLartosPointAltitude());
  QStandardItem *typeCol = new QStandardItem(point.getCoordinatesType());

  model->appendRow( QList<QStandardItem*>() << nameCol << latCol << longCol << atiCol << typeCol);
  ui->point_listView->resizeColumnsToContents();
  ui->point_listView->resizeRowsToContents();
}

void ResultSelection::initTableView(){
    horizontalHeader.append("Point Name");
    if(coordinate_type == "utm")
    {
        horizontalHeader.append("Northing");
        horizontalHeader.append("Easting");
        txtLat = "N: ";
        txtLong = "E: ";
    }
    else if(coordinate_type == "xy")
    {
        horizontalHeader.append("X");
        horizontalHeader.append("Y");
        txtLat = "X: ";
        txtLong = "Y: ";
    }
    else if(coordinate_type == "bl")
    {
        horizontalHeader.append("Latitude");
        horizontalHeader.append("Longitude");
        txtLat = "Lat:";
        txtLong = "Long:";
    }
    horizontalHeader.append("H");
    horizontalHeader.append("Type");
    model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->point_listView->setModel(model);

    ui->point_listView->verticalHeader()->setVisible(false);
    ui->point_listView->verticalHeader()->setDefaultSectionSize(15);
    ui->point_listView->setEnabled(true);
    ui->point_listView->setShowGrid(false);

    QFont fontHeader = ui->point_listView->horizontalHeader()->font();
    fontHeader.setPointSize(42);
    ui->point_listView->horizontalHeader()->setFont(fontHeader);
    ui->point_listView->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 18pt; }");
}

void ResultSelection::switchToBG()
{
    ui->lblCurrentPos->setText(lblCurrentPositionTxt_BG);
    ui->lblCurrentPos->adjustSize();
    ui->lblCurrentPos->setGeometry(
                (this->width() - ui->lblCurrentPos->width())/2,
                ui->lblCurrentPos->geometry().y(),
                ui->lblCurrentPos->width(),
                ui->lblCurrentPos->height());

    ui->lblNewPos->setText(lblNewPositionTxt_BG);
    ui->lblNewPos->adjustSize();
    ui->lblNewPos->setGeometry(
                (this->width() - ui->lblNewPos->width())/2,
                ui->lblNewPos->geometry().y(),
                ui->lblNewPos->width(),
                ui->lblNewPos->height());

    ui->lblWantToUse->setText(lblWantToUseTxt_BG);
    ui->lblWantToUse->adjustSize();
    ui->lblWantToUse->setGeometry(
                (this->width() - ui->lblWantToUse->width())/2,
                ui->lblWantToUse->geometry().y(),
                ui->lblWantToUse->width(),
                ui->lblWantToUse->height());

    ui->lblCurrentDirAngle->setText(lblCurrentAngleTxt_BG);
    ui->lblCurrentDirAngle->adjustSize();
    ui->lblCurrentDirAngle->setGeometry(
                (this->width() - ui->lblCurrentDirAngle->width())/2,
                ui->lblCurrentDirAngle->geometry().y(),
                ui->lblCurrentDirAngle->width(),
                ui->lblCurrentDirAngle->height());

    ui->lblNewDirAngle->setText(lblNewAngleTxt_BG);
    ui->lblNewDirAngle->adjustSize();
    ui->lblNewDirAngle->setGeometry(
                (this->width() - ui->lblNewDirAngle->width())/2,
                ui->lblNewDirAngle->geometry().y(),
                ui->lblNewDirAngle->width(),
                ui->lblNewDirAngle->height());

    ui->lblWantToUseAngle->setText(lblWantToUseAngleTxt_BG);
    ui->lblWantToUseAngle->adjustSize();
    ui->lblWantToUseAngle->setGeometry(
                (this->width() - ui->lblWantToUseAngle->width())/2,
                ui->lblWantToUseAngle->geometry().y(),
                ui->lblWantToUseAngle->width(),
                ui->lblWantToUseAngle->height());

    ui->btnChoose->setText(btnChooseTxt_BG);
    ui->btnUse->setText(btnUseTxt_BG);
    ui->btnNo->setText(btnNoTxt_BG);
    ui->btnUseDirAngle->setText(btnUseTxt_BG);
    ui->btnNo_2->setText(btnNoTxt_BG);

    flgBG_rs = true;
}

void ResultSelection::switchToEN()
{
    ui->lblCurrentPos->setText(lblCurrentPositionTxt_EN);
    ui->lblCurrentPos->adjustSize();
    ui->lblCurrentPos->setGeometry(
                (this->width() - ui->lblCurrentPos->width())/2,
                ui->lblCurrentPos->geometry().y(),
                ui->lblCurrentPos->width(),
                ui->lblCurrentPos->height());

    ui->lblNewPos->setText(lblNewPositionTxt_EN);
    ui->lblNewPos->adjustSize();
    ui->lblNewPos->setGeometry(
                (this->width() - ui->lblNewPos->width())/2,
                ui->lblNewPos->geometry().y(),
                ui->lblNewPos->width(),
                ui->lblNewPos->height());

    ui->lblWantToUse->setText(lblWantToUseTxt_EN);
    ui->lblWantToUse->adjustSize();
    ui->lblWantToUse->setGeometry(
                (this->width() - ui->lblWantToUse->width())/2,
                ui->lblWantToUse->geometry().y(),
                ui->lblWantToUse->width(),
                ui->lblWantToUse->height());

    ui->lblCurrentDirAngle->setText(lblCurrentAngleTxt_EN);
    ui->lblCurrentDirAngle->adjustSize();
    ui->lblCurrentDirAngle->setGeometry(
                (this->width() - ui->lblCurrentDirAngle->width())/2,
                ui->lblCurrentDirAngle->geometry().y(),
                ui->lblCurrentDirAngle->width(),
                ui->lblCurrentDirAngle->height());

    ui->lblNewDirAngle->setText(lblNewAngleTxt_EN);
    ui->lblNewDirAngle->adjustSize();
    ui->lblNewDirAngle->setGeometry(
                (this->width() - ui->lblNewDirAngle->width())/2,
                ui->lblNewDirAngle->geometry().y(),
                ui->lblNewDirAngle->width(),
                ui->lblNewDirAngle->height());

    ui->lblWantToUseAngle->setText(lblWantToUseAngleTxt_EN);
    ui->lblWantToUseAngle->adjustSize();
    ui->lblWantToUseAngle->setGeometry(
                (this->width() - ui->lblWantToUseAngle->width())/2,
                ui->lblWantToUseAngle->geometry().y(),
                ui->lblWantToUseAngle->width(),
                ui->lblWantToUseAngle->height());


    ui->btnChoose->setText(btnChooseTxt_EN);
    ui->btnUse->setText(btnUseTxt_EN);
    ui->btnNo->setText(btnNoTxt_EN);
    ui->btnUseDirAngle->setText(btnUseTxt_EN);
    ui->btnNo_2->setText(btnNoTxt_EN);

    flgBG_rs = false;
}

void ResultSelection::on_btnUse_pressed()
{
    btnUse_pressed();
}


void ResultSelection::on_btnUse_released()
{
    btnUse_released();
    ui->grBoxUpdatePosition->hide();
    X_parameter = newLat;
    Y_parameter = newLong;
    calculatedLat = newLat;
    calculatedLong = newLong;
    updateCoordinates = true;
}


void ResultSelection::on_btnNo_pressed()
{
    btnNo_pressed();
}


void ResultSelection::on_btnNo_released()
{
    btnNo_released();
    ui->grBoxUpdatePosition->hide();
    ui->grBoxPoints->show();
    this->close();
}

void ResultSelection::btnUse_pressed()
{
    ui->btnUse->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void ResultSelection::btnUse_released()
{
    ui->btnUse->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: lightgray;"
                );
}

void ResultSelection::btnUse_selected()
{
    ui->btnUse->setStyleSheet(
                "border: 2px solid lightgray;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void ResultSelection::btnNo_pressed()
{
    ui->btnNo->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void ResultSelection::btnNo_released()
{
    ui->btnNo->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: lightgray;"
                );
}

void ResultSelection::btnNo_selected()
{
    ui->btnNo->setStyleSheet(
                "border: 2px solid lightgray;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void ResultSelection::btnUseDirAngle_pressed()
{
    ui->btnUseDirAngle->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void ResultSelection::btnUseDirAngle_released()
{
    ui->btnUseDirAngle->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: lightgray;"
                );
}

void ResultSelection::btnUseDirAngle_selected()
{
    ui->btnUseDirAngle->setStyleSheet(
                "border: 2px solid lightgray;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void ResultSelection::btnNo_2_pressed()
{
    ui->btnNo_2->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void ResultSelection::btnNo_2_released()
{
    ui->btnNo_2->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: lightgray;"
                );
}

void ResultSelection::btnNo_2_selected()
{
    ui->btnNo_2->setStyleSheet(
                "border: 2px solid lightgray;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}


void ResultSelection::btnChoose_pressed()
{
    ui->btnChoose->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void ResultSelection::btnChoose_released()
{
    ui->btnChoose->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: lightgray;"
                );
}

void ResultSelection::btnChoose_selected()
{
    ui->btnChoose->setStyleSheet(
                "border: 2px solid lightgray;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void ResultSelection::btnClose_pressed()
{
    ui->btnClose->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void ResultSelection::btnClose_released()
{
    ui->btnClose->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: lightgray;"
                );
}


void ResultSelection::on_btnChoose_pressed()
{
    btnChoose_pressed();
    if(pointIndex.isValid())
    {
        int row = pointIndex.row();
        currLat = pointIndex.sibling(row, 1).data().toString();
        currLong = pointIndex.sibling(row, 2).data().toString();
        currAlt = pointIndex.sibling(row, 3).data().toString();
    }
}


void ResultSelection::on_btnChoose_released()
{
    btnChoose_released();
    insertPoint = true;

    if(selectedPoint!="0")
    {
        if(pointIndex.isValid())
        {
            this->close();
        }
    }
}

void ResultSelection::gpioBtnOk()
{
    if(ui->btnUse->hasFocus())
    {
        on_btnUse_pressed();
        on_btnUse_released();
    }
    else if(ui->btnNo->hasFocus())
    {
        on_btnNo_pressed();
        on_btnNo_released();
    }
    else if(ui->btnChoose->hasFocus())
    {
        on_btnChoose_pressed();
        on_btnChoose_released();
    }
    else if(ui->btnUseDirAngle->hasFocus())
    {
        on_btnUseDirAngle_pressed();
        on_btnUseDirAngle_released();
    }
    else if(ui->btnNo_2->hasFocus())
    {
        on_btnNo_2_pressed();
        on_btnNo_2_released();
    }
}

void ResultSelection::gpioBtnLeft()
{
    if(ui->btnNo->hasFocus())
    {
        btnNo_released();
        ui->btnUse->setFocus();
        btnUse_selected();
    }
    else if(ui->btnNo_2->hasFocus())
    {
        btnNo_2_released();
        ui->btnUseDirAngle->setFocus();
        btnUseDirAngle_selected();
    }
}

void ResultSelection::gpioBtnRight()
{
    if(ui->btnUse->hasFocus())
    {
        btnUse_released();
        ui->btnNo->setFocus();
        btnNo_selected();
    }
    else if(ui->btnUseDirAngle->hasFocus())
    {
        btnUseDirAngle_released();
        ui->btnNo_2->setFocus();
        btnNo_2_selected();
    }
}


void ResultSelection::on_point_listView_pressed(const QModelIndex &index)
{
    pointIndex = index;
    if(pointIndex.isValid())
    {
        ui->pointA->setEnabled(true);
        ui->pointB->setEnabled(true);
        ui->pointC->setEnabled(true);
        ui->pointD->setEnabled(true);
    }
}
  

void ResultSelection::on_pointA_pressed()
{
    selectedPoint = "A";

    pointB_released();
    pointC_released();
    pointD_released();

    ui->pointA->setStyleSheet(
                "border: 2px black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: black; "
                "color: white;"
                );
}

void ResultSelection::pointA_released()
{
    ui->pointA->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173); "
                "color: black;"
                );
}

void ResultSelection::on_pointB_pressed()
{
    selectedPoint = "B";

    pointA_released();
    pointC_released();
    pointD_released();

    ui->pointB->setStyleSheet(
                "border: 2px black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: black; "
                "color: white;"
                );
}

void ResultSelection::pointB_released()
{
    ui->pointB->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173); "
                "color: black;"
                );
}

void ResultSelection::on_pointC_pressed()
{
    selectedPoint = "C";

    pointA_released();
    pointB_released();
    pointD_released();

    ui->pointC->setStyleSheet(
                "border: 2px black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: black; "
                "color: white;"
                );
}

void ResultSelection::pointC_released()
{
    ui->pointC->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173); "
                "color: black;"
                );
}

void ResultSelection::on_pointD_pressed()
{
    selectedPoint = "D";

    pointA_released();
    pointB_released();
    pointC_released();

    ui->pointD->setStyleSheet(
                "border: 2px black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: black; "
                "color: white;"
                );
}

void ResultSelection::pointD_released()
{
    ui->pointD->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173); "
                "color: black;"
                );
}

void ResultSelection::on_btnClose_pressed()
{
    btnClose_pressed();
}

void ResultSelection::on_btnClose_released()
{
    btnClose_released();
    insertPoint = false;
    this->close();
}

void ResultSelection::on_btnUseDirAngle_pressed()
{
    btnUseDirAngle_pressed();
}


void ResultSelection::on_btnUseDirAngle_released()
{
    btnUseDirAngle_released();
    ui->grBoxUpdateDirAngle->hide();
    calculatedDirAngle = alfa_deg;
    updateDirAngle = true;
}


void ResultSelection::on_btnNo_2_pressed()
{
    btnNo_2_pressed();
}


void ResultSelection::on_btnNo_2_released()
{
    btnNo_2_released();
    ui->grBoxUpdateDirAngle->hide();
    ui->grBoxPoints->show();
    this->close();
}


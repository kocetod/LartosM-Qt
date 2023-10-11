#include "dialogprogress.h"
#include "ui_dialogprogress.h"

DialogProgress::DialogProgress(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogProgress)
{
  ui->setupUi(this);
}

DialogProgress::~DialogProgress()
{
  delete ui;
}

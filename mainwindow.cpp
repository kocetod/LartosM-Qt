#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "expanded.h"
#include "ui_expanded.h"

#include "tasks.h"
#include "ui_tasks.h"

#include "menu.h"
#include "ui_menu.h"

#include "Hik/hikvision.h"
#include "variables.h"
#include "Hik/global.h"
#include "Hik/CaptureThread.h"
#include "Hik/Controller.h"

#include "bg.h"
#include "en.h"

#include "mediabrowser.h" 

#include "resultselection.h"
#include "TransLib/geodw.h"

#include <QDesktopWidget>
#include <QScreen>
#include <QKeyEvent>
#include <QTimer>

QTimer* timer = new QTimer();

extern "C"
{
#include "Periph/HikCameraDraw.h"
#include "Periph/LucidCameraDraw.h"
}
/*
QMainWindow* findMainWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        QMainWindow* pMainWnd = qobject_cast<QMainWindow*>(pWidget);
        if (pMainWnd)
            return pMainWnd;
    }
    return nullptr;
}

int updateFrameCount =0;

QPixmap updateFrameDayCam(){

    QPixmap pixmap;
    if(DaycamDrawIsRunning()==true)
    {
        const uchar* buffer = (unsigned char*)GetLucidImageBuffer();
        QImageCleanupFunction cleanupFunction = NULL;

        long int width = GetDaycamImageWidth();
        long int height = GetDaycamImageHeight();

        QImage image(buffer, width, height, QImage::Format_RGBA8888, cleanupFunction, NULL );
        image = image.mirrored(false,true);
        pixmap = pixmap.fromImage(image.scaled(currentVideoPanelX,currentVideoPanelY,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

        if(currentVideoPanel!=NULL) 
        {
            currentVideoPanel->setPixmap(pixmap);
        }

        return pixmap;
    }
    return pixmap;
}*/
/*
void TestCallback()
{
    updateFrameDayCam();
}*/
/*
void MainWindow::setThermalCameraParameters(){
    hikVision->setBrightness(saveuserdata->getBrightnessValueParameter());
    hikVision->setContrast(saveuserdata->getContrastValueParameter());
    if(saveuserdata->getDeeModeParameter()){
        hikVision->setDde(saveuserdata->getDeeValueParameter());
    }
}*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->lblx->hide();
    //ui->lbly->hide();
    //ui->lblh->hide();

    this->setWindowFlags(Qt::FramelessWindowHint);
    qApp->installEventFilter(this);

    saveuserdata = new SaveLartosUserData;
    float xAxisParameter = saveuserdata->getReticlePositionXasisParameter().toFloat();
    float yAxisParameter = saveuserdata->getReticlePositionYasisParameter().toFloat();

    SetCrosshairDisplacementValue(xAxisParameter, yAxisParameter);

    //ui->lblx->setText(QString().setNum(X_parameter, 'g', 10));
    //ui->lbly->setText(QString().setNum(Y_parameter, 'g', 10));
    //ui->lblh->setText(QString().setNum(H_parameter, 'g', 6));
    //open_mediaBrowser = new MediaBrowser;
    setAttribute(Qt::WA_AcceptTouchEvents, true);

    ui->btnNuc->setEnabled(false);
    ui->btnPantilt_up->hide();
    ui->btnPantilt_down->hide();
    ui->btnPantilt_left->hide();
    ui->btnPantilt_right->hide();
    ui->btnLRF->setFocus();

    updateCoordParameters();


    if(GetSelectedCamera()==THERMALCAM)
    {
        SelectCamera(DAYCAM);
    }

    currentVideoPanelX = 990;
    currentVideoPanelY = 700;
    currentVideoPanel = ui->frameLabel; 
    connect(thermController->processingThread,SIGNAL(newFrame(QPixmap)),this,SLOT(updateFrame(QPixmap)));
}

QIcon *zoom1x = new QIcon();
QIcon *zoom2x = new QIcon();
QIcon *zoom4x = new QIcon();
QIcon *zoom8x = new QIcon();
QIcon *zoom16x = new QIcon();

void MainWindow::setIconPixmap()
{
    zoom1x->addPixmap(QPixmap(":/new/prefix1/icons/zoom1.png"), QIcon::Normal, QIcon::On);
    zoom2x->addPixmap(QPixmap(":/new/prefix1/icons/zoom2.png"), QIcon::Normal, QIcon::On);
    zoom4x->addPixmap(QPixmap(":/new/prefix1/icons/zoom4.png"), QIcon::Normal, QIcon::On);
    zoom8x->addPixmap(QPixmap(":/new/prefix1/icons/zoom8.png"), QIcon::Normal, QIcon::On);
    zoom16x->addPixmap(QPixmap(":/new/prefix1/icons/zoom16.png"),QIcon::Normal, QIcon::On);
}

void MainWindow::setDayZoom()
{
    setIconPixmap();

    if(day_zoom == "1X")
    {
        ui->btnZoom->setIcon(*zoom1x);
    }
    else if(day_zoom == "2X")
    {
        ui->btnZoom->setIcon(*zoom2x);
    }
    else if(day_zoom == "4X")
    {
        ui->btnZoom->setIcon(*zoom4x);
    }
    else if(day_zoom == "8X")
    {
        ui->btnZoom->setIcon(*zoom8x);
    }
    else if(day_zoom == "16X")
    {
        ui->btnZoom->setIcon(*zoom16x);
    }
}

void MainWindow::setIrZoom()
{
    setIconPixmap();

    if(ir_zoom == "1X")
    {
        ui->btnZoom->setIcon(*zoom1x);
    }
    else if(ir_zoom == "2X")
    {
        ui->btnZoom->setIcon(*zoom2x);
    }
    else if(ir_zoom == "4X")
    {
        ui->btnZoom->setIcon(*zoom4x);
    }
    else if(ir_zoom == "8X")
    {
        ui->btnZoom->setIcon(*zoom8x);
    }
}

void MainWindow::setIrPolarity()
{
    if(polarity_ir == true)
    {
        btnPolarity_pressed();
    }
    else if(polarity_ir == false)
    {
        btnPolarity_released();
    }
}

void MainWindow::setDayPolarity()
{
    if(polarity_day == true)
    {
        btnPolarity_pressed();
    }
    else if(polarity_day == false)
    {
        btnPolarity_released();
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this && event->type() == QEvent::WindowUnblocked)
    {
        currentVideoPanelX = 1000;
        currentVideoPanelY = 700;
        currentVideoPanel = ui->frameLabel;

        if(day_ir == true)
        {
            btnDayir_pressed();
            setIrZoom();
            setIrPolarity();
        }
        else if(day_ir == false)
        {
            btnDayir_released();
            setDayZoom();
            setDayPolarity();
        }

        if(flgBG_w == true)
        {
            switchToBG();
        }
        else if(flgBG_w == false)
        {
            switchToEN();
        } 

        //ui->lblx->setText(QString().setNum(X_parameter, 'g', 10));
        //ui->lbly->setText(QString().setNum(Y_parameter, 'g', 10));
        //ui->lblh->setText(QString().setNum(H_parameter, 'g', 6));

        updateCoordParameters();
    }
    return QObject::eventFilter(obj, event);
} 


void MainWindow::updateFrame(const QPixmap &frame)
{
    if(currentVideoPanel==ui->frameLabel)
    {
        ui->frameLabel->setPixmap(frame);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnLrf_pressed()
{
    ui->btnLRF->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnLrf_released()
{
    ui->btnLRF->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void MainWindow::btnLrf_selected()
{
    ui->btnLRF->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnDayir_pressed()
{
    ui->btnDayir->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnDayir_released()
{
    ui->btnDayir->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void MainWindow::btnDayir_selected()
{
    ui->btnDayir->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnPantilt_pressed()
{
    ui->btnPantilt->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnPantilt_released()
{
    ui->btnPantilt->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void MainWindow::btnPantilt_selected()
{
    ui->btnPantilt->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnMedia_pressed()
{
    ui->btnMedia->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnMedia_released()
{
    ui->btnMedia->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void MainWindow::btnMedia_selected()
{
    ui->btnMedia->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnTasks_pressed()
{
    ui->btnTasks->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnTasks_released()
{
    ui->btnTasks->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void MainWindow::btnTasks_selected()
{
    ui->btnTasks->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnNuc_pressed()
{
    ui->btnNuc->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnNuc_released()
{
    ui->btnNuc->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void MainWindow::btnNuc_selected()
{
    ui->btnNuc->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnZoom_pressed()
{
    ui->btnZoom->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnZoom_released()
{
    ui->btnZoom->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void MainWindow::btnZoom_selected()
{
    ui->btnZoom->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnPolarity_pressed()
{
    ui->btnPolarity->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"

                );
}


void MainWindow::btnPolarity_released()
{
    ui->btnPolarity->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void MainWindow::btnPolarity_selected()
{
    ui->btnPolarity->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnMenu_pressed()
{
    ui->btnMenu->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnMenu_released()
{
    ui->btnMenu->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void MainWindow::btnMenu_selected()
{
    ui->btnMenu->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnScreenshot_pressed()
{
    ui->btnScreenshot->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnScreenshot_released()
{
    ui->btnScreenshot->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void MainWindow::btnScreenshot_selected()
{
    ui->btnScreenshot->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}


void MainWindow::btnExpand_pressed()
{
    ui->btnExpand->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}


void MainWindow::btnExpand_released()
{
    ui->btnExpand->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0); "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnExpand_selected()
{
    ui->btnExpand->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}


void MainWindow::btnPantilt_up_pressed()
{
    ui->btnPantilt_up->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnPantilt_up_released()
{
    ui->btnPantilt_up->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnPantilt_up_selected()
{
    ui->btnPantilt_up->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnPantilt_down_pressed()
{
    ui->btnPantilt_down->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnPantilt_down_released()
{
    ui->btnPantilt_down->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnPantilt_down_selected()
{
    ui->btnPantilt_down->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnPantilt_left_pressed()
{
    ui->btnPantilt_left->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnPantilt_left_released()
{
    ui->btnPantilt_left->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnPantilt_left_selected()
{
    ui->btnPantilt_left->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnPantilt_right_pressed()
{
    ui->btnPantilt_right->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnPantilt_right_released()
{
    ui->btnPantilt_right->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::btnPantilt_right_selected()
{
    ui->btnPantilt_right->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void MainWindow::switchToBG()
{
    flgBG_w = true;
}

void MainWindow::switchToEN()
{
    flgBG_w = false;
}

void MainWindow::hidePanTilt()
{
    ui->btnPantilt_up->hide();
    ui->btnPantilt_down->hide();
    ui->btnPantilt_left->hide();
    ui->btnPantilt_right->hide();
}

void MainWindow::showPanTilt()
{
    ui->btnPantilt_up->show();
    ui->btnPantilt_down->show();
    ui->btnPantilt_left->show();
    ui->btnPantilt_right->show();
}

void MainWindow::makeScreenshot()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0, this->geometry().x(), this->geometry().y(), this->width(), this->height());

    QDateTime now = QDateTime::currentDateTime();
    QString timestamp = now.toString(QLatin1String("dd.MM.yyyy hh-mm-ss"));

    QString directory = "/LartosImages";
    QDir pathToDir;
    qDebug() << directory;
    auto fileName = QString(pathToDir.homePath()  + directory  + "/" + timestamp + ".bmp");
    pixmap.save(fileName);
}

void MainWindow::on_btnMedia_pressed()
{
    btnLrf_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }
    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    btnMedia_pressed();
}

void MainWindow::openMediaBrowser()
{
    open_mediaBrowser.setModal(true);

    if(flgBG_w == true)
    {
        open_mediaBrowser.switchToBG();
    }
    else if(flgBG_w == false)
    {
        open_mediaBrowser.switchToEN();
    }
    open_mediaBrowser.listFiles();
    open_mediaBrowser.exec();
}

void MainWindow::on_btnMedia_released()
{
    btnMedia_released();

    openMediaBrowser();
}

void MainWindow::on_btnExpand_pressed()
{
    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    btnExpand_pressed();
}

void MainWindow::openTasksWin()
{
    Tasks t;
    t.setModal(true);
    t.show();

    if(flgBG_w == true)
    {
        t.switchToBG();
    }
    else if(flgBG_w == false)
    {
        t.switchToEN();
    }
    t.exec();
}

void MainWindow::on_btnTasks_released()
{
    btnTasks_released();
    openTasksWin();
}

void MainWindow::on_btnZoom_pressed()
{
    btnZoom_pressed();
    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    changeZoom();
}

void MainWindow::changeZoom()
{
    if(day_ir == true)
    {
        checkIrZoom();
    }
    else if(day_ir == false)
    {
        checkDayZoom();
    }
}

void MainWindow::on_btnZoom_released()
{
    btnZoom_released();
}

void MainWindow::openMenuWin()
{
    Menu m;
    m.setModal(true);
    m.showFullScreen();
    //m.show();
    if(flgBG_w == true)
    {
        m.switchToBG();
    }
    else if(flgBG_w == false)
    {
        m.switchToEN();
    }
    m.exec();
}

void MainWindow::on_btnMenu_released()
{
    btnMenu_released();

     currentVideoPanel = NULL;

    openMenuWin();
}

QIcon *day = new QIcon();
QIcon *thermal = new QIcon();
void MainWindow::on_btnDayir_pressed()
{
    day->addPixmap(QPixmap(":/new/prefix1/icons/day.png"), QIcon::Normal, QIcon::On);
    thermal->addPixmap(QPixmap(":/new/prefix1/icons/thermal.png"), QIcon::Normal, QIcon::On);

    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    } 


    if(GetSelectedCamera()==DAYCAM)  

    {
        if(SelectCamera(THERMALCAM)==true)
        {
            btnDayir_pressed();

            ui->btnNuc->setEnabled(true);
            ui->btnNuc->setStyleSheet(
                        "border: 2px white; "
                        "border-radius: 10px;"
                        "padding: 0 8px;"
                        "background: white;"
                        "color: black;"
                        );

            if(polarity_ir == true)
            {
                btnPolarity_pressed();
            }
            else if(polarity_ir == false)
            {
                btnPolarity_released();
            }

            setIrZoom();
            ui->btnDayir->setIcon(*thermal);

            day_ir = true;
        }
    }
    else if(GetSelectedCamera()==THERMALCAM)
    {
        if(SelectCamera(DAYCAM)==true)
        {
            btnDayir_released();

            ui->btnNuc->setStyleSheet(
                        "border: 2px white; "
                        "border-radius: 10px;"
                        "padding: 0 8px;"
                        "background: white;"
                        "color: gray;"
                        );
            ui->btnNuc->setEnabled(false);

            if(polarity_day == true)
            {
                btnPolarity_pressed();
            }
            else if(polarity_day == false)
            {
                btnPolarity_released();
            }

            setDayZoom();

            ui->btnDayir->setIcon(*day);
            day_ir = false;
        }
    }
}

void MainWindow::on_btnTasks_pressed()
{
    btnLrf_released();
    btnMedia_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    btnTasks_pressed();
}

void MainWindow::on_btnMenu_pressed()
{
    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    btnMenu_pressed();
}

void MainWindow::openExpandedWin()
{
    Expanded ex;
    ex.setModal(true);
    ex.showFullScreen();
    ex.taskStyle();

    if(flgBG_w == true)
    {
        ex.switchToBG();
    }
    else if(flgBG_w == false)
    {
        ex.switchToEN();
    }

    ex.exec();
}

void MainWindow::on_btnExpand_released()
{
    btnExpand_released();

    //if(day_ir == true)
    //{
    //    ir_zoom = ui->btnZoom->text();
    //}
    //else if(day_ir == false)
    //{
    //    day_zoom = ui->btnZoom->text();
    //}
    currentVideoPanel = NULL;

    openExpandedWin();
}

QIcon *shutter_open = new QIcon();
void MainWindow::on_btnNuc_pressed()
{
    shutter_open->addPixmap(QPixmap(":/new/prefix1/icons/shutter_open.png"),QIcon::Normal, QIcon::On);

    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    btnNuc_pressed();
    ui->btnNuc->setIcon(*shutter_open);
    hikVision->doNuc();
}

void MainWindow::on_btnScreenshot_pressed()
{
    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    btnScreenshot_pressed();
}

void MainWindow::on_btnScreenshot_released()
{
    btnScreenshot_released();

    makeScreenshot();
}

void MainWindow::on_btnPolarity_pressed()
{
    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();

        if(polarity_day == false)
        {
            btnPolarity_pressed(); 
            polarity_day = true;
        } 
        else if(polarity_day == true)
        {
            btnPolarity_released(); 
            polarity_day = false;
        }
        SetGrayscaleOn(polarity_day);
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_pressed();
            hikVision->setPolarity(1);
            polarity_ir = true;
        }
        else if(polarity_ir == true)
        {
            btnPolarity_released();
            hikVision->setPolarity(2);
            polarity_ir = false;
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }
}

QIcon *shutter_closed = new QIcon();
void MainWindow::on_btnNuc_released()
{
    shutter_closed->addPixmap(QPixmap(":/new/prefix1/icons/shutter_closed.png"),QIcon::Normal, QIcon::On);
    ui->btnNuc->setIcon(*shutter_closed);
    btnNuc_released();
}

void MainWindow::on_btnPantilt_pressed()
{   
    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    if(pantilt_ == false)
    {
        btnPantilt_pressed();

        showPanTilt();

        pantilt_ = true;
    }
    else if(pantilt_ == true)
    {
        btnPantilt_released();

        hidePanTilt();

        pantilt_ = false;
    }
}

int MainWinPanSpeedCallback()
{
    return mainWinPanSpeed;
}

int MainWinTiltSpeedCallback()
{
    return mainWinTiltSpeed;
}

void MainWindow::increaseUpSpeed()
{
    if(mainWinTiltSpeed < 100000)
    {
        mainWinTiltSpeed+=5000;
    }
}
void MainWindow::decreaseUpSpeed()
{
    if(mainWinTiltSpeed > 100)
    {
        mainWinTiltSpeed-=5000;
    }
    else if(mainWinTiltSpeed == 100)
    {
        mainWinTiltSpeed = 0;
    }
    //ui->lblx->setText(QString::number(mainWinTiltSpeed));
}

void MainWindow::increaseDownSpeed()
{
    if(mainWinTiltSpeed > -100000)
    {
        mainWinTiltSpeed-=5000;
        //ui->lblx->setText(QString::number(mainWinTiltSpeed));
    }
}
void MainWindow::decreaseDownSpeed()
{
    if(mainWinTiltSpeed < -100)
    {
        mainWinTiltSpeed+=5000;
    }
    else if(mainWinTiltSpeed == -100)
    {
        mainWinTiltSpeed = 0;
    }
    //ui->lblx->setText(QString::number(mainWinTiltSpeed));
}

void MainWindow::increaseLeftSpeed()
{
    if(mainWinPanSpeed > -100000)
    {
        mainWinPanSpeed-=5000;
        //ui->lbly->setText(QString::number(mainWinPanSpeed));
    }
}
void MainWindow::decreaseLeftSpeed()
{
    if(mainWinPanSpeed < -100)
    {
        mainWinPanSpeed+=5000;
    }
    else if(mainWinPanSpeed == -100)
    {
        mainWinPanSpeed = 0;
    }
    //ui->lbly->setText(QString::number(mainWinPanSpeed));
}

void MainWindow::increaseRightSpeed()
{
    if(mainWinPanSpeed < 100000)
    {
        mainWinPanSpeed+=5000;
        //ui->lbly->setText(QString::number(mainWinPanSpeed));
    }
}
void MainWindow::decreaseRightSpeed()
{
    if(mainWinPanSpeed > 100)
    {
        mainWinPanSpeed-=5000;
    }
    else if(mainWinPanSpeed == 100)
    {
        mainWinPanSpeed = 0;
    }
    //ui->lbly->setText(QString::number(mainWinPanSpeed));
}

void MainWindow::startIncreasingUp()
{
    timer->stop();
    mainWinTiltSpeed = 5000;

    if(timer)
    {
        timer->deleteLater();
    }

    timer = new QTimer;
    timer->start(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(increaseUpSpeed()));
    if(mainWinTiltSpeed == 100000)
    {
        timer->stop();
        timer->deleteLater();
    }
}
void MainWindow::startIncreasingDown()
{
    timer->stop();
    mainWinTiltSpeed = -5000;

    if(timer)
    {
        timer->deleteLater();
    }

    timer = new QTimer;
    timer->start(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(increaseDownSpeed()));
    if(mainWinTiltSpeed == -100000)
    {
        timer->stop();
        timer->deleteLater();
    }
}
void MainWindow::startIncreasingLeft()
{
    timer->stop();
    mainWinPanSpeed = -5000;

    if(timer)
    {
        timer->deleteLater();
    }

    timer = new QTimer;
    timer->start(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(increaseLeftSpeed()));
    if(mainWinPanSpeed == -100000)
    {
        timer->stop();
        timer->deleteLater();
    }
}
void MainWindow::startIncreasingRight()
{
    timer->stop();
    mainWinPanSpeed = 5000;

    if(timer)
    {
        timer->deleteLater();
    }

    timer = new QTimer;
    timer->start(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(increaseRightSpeed()));
    if(mainWinPanSpeed == 100000)
    {
        timer->stop();
        timer->deleteLater();
    }
}

void MainWindow::on_btnPantilt_up_pressed()
{
    mainWinPanSpeed = 0;
    //ui->lbly->setText(QString::number(mainWinPanSpeed));
    mainWinTiltSpeed = 100;
    //ui->lblx->setText(QString::number(mainWinTiltSpeed));

    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    btnPantilt_up_pressed();

    if(timer)
    {
        timer->deleteLater();
    }

    timer = new QTimer;
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(startIncreasingUp()));
}

void MainWindow::on_btnPantilt_up_released()
{
    //mainWinTiltSpeed = 0;
    //ui->lblx->setText(QString::number(mainWinTiltSpeed));

    timer->stop();
    btnPantilt_up_released();

    if(timer)
    {
        timer->deleteLater();
    }

    timer = new QTimer;
    timer->start(25);
    connect(timer, SIGNAL(timeout()), this, SLOT(decreaseUpSpeed()));
    if(mainWinTiltSpeed == 0)
    {
        timer->stop();
    }
}

void MainWindow::on_btnPantilt_down_pressed()
{
    mainWinPanSpeed = 0;
    //ui->lbly->setText(QString::number(mainWinPanSpeed));
    mainWinTiltSpeed = -100;
    //ui->lblx->setText(QString::number(mainWinTiltSpeed));

    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    btnPantilt_down_pressed();

    if(timer)
    {
        timer->deleteLater();
    }
    timer = new QTimer;
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(startIncreasingDown()));
}

void MainWindow::on_btnPantilt_down_released()
{
    //mainWinTiltSpeed = 0;
    //ui->lblx->setText(QString::number(mainWinTiltSpeed));

    timer->stop();
    btnPantilt_down_released();

    if(timer)
    {
        timer->deleteLater();
    }
    timer = new QTimer;
    timer->start(25);
    connect(timer, SIGNAL(timeout()), this, SLOT(decreaseDownSpeed()));
    if(mainWinTiltSpeed == 0)
    {
        timer->stop();
    }
}

void MainWindow::on_btnPantilt_left_pressed()
{
    mainWinTiltSpeed = 0;
    //ui->lblx->setText(QString::number(mainWinTiltSpeed));
    mainWinPanSpeed = -100;
    //ui->lbly->setText(QString::number(mainWinPanSpeed));

    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    btnPantilt_left_pressed();

    if(timer)
    {
        timer->deleteLater();
    }
    timer = new QTimer;
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(startIncreasingLeft()));
}

void MainWindow::on_btnPantilt_left_released()
{
    //mainWinPanSpeed = 0;
    //ui->lbly->setText(QString::number(mainWinPanSpeed));

    timer->stop();
    btnPantilt_left_released();

    if(timer)
    {
        timer->deleteLater();
    }
    timer = new QTimer;
    timer->start(25);
    connect(timer, SIGNAL(timeout()), this, SLOT(decreaseLeftSpeed()));
    if(mainWinPanSpeed == 0)
    {
        timer->stop();
    }
}

void MainWindow::on_btnPantilt_right_pressed()
{
    mainWinTiltSpeed = 0;
    //ui->lblx->setText(QString::number(mainWinTiltSpeed));
    mainWinPanSpeed = 100;
    //ui->lbly->setText(QString::number(mainWinPanSpeed));

    btnLrf_released();
    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    btnPantilt_right_pressed();

    if(timer)
    {
        timer->deleteLater();
    }
    timer = new QTimer;
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(startIncreasingRight()));
}

void MainWindow::on_btnPantilt_right_released()
{
    //mainWinPanSpeed = 0;
    //ui->lbly->setText(QString::number(mainWinPanSpeed));

    timer->stop();
    btnPantilt_right_released();

    if(timer)
    {
        timer->deleteLater();
    }
    timer = new QTimer;
    timer->start(25);
    connect(timer, SIGNAL(timeout()), this, SLOT(decreaseRightSpeed()));
    if(mainWinPanSpeed == 0)
    {
        timer->stop();
    }
}

void MainWindow::on_btnLRF_pressed()
{
    RfRequestMeasurement();

    btnMedia_released();
    btnTasks_released();
    btnZoom_released();
    btnMenu_released();
    btnScreenshot_released();
    btnExpand_released();

    if(day_ir == false)
    {
        btnDayir_released();
        if(polarity_day == false)
        {
            btnPolarity_released();
        }
    }
    else if(day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_released();
        }
    }

    if(pantilt_ == false)
    {
        btnPantilt_released();
    }

    if(ui->btnNuc->isEnabled())
    {
        btnNuc_released();
    }

    btnLrf_pressed();
}

void MainWindow::on_btnLRF_released()
{
    btnLrf_released();
}

void MainWindow::gpioBtnOk()
{
    if(ui->btnLRF->hasFocus())
    {

    }
    else if(ui->btnDayir->hasFocus())
    {
        on_btnDayir_pressed();
        btnDayir_selected();
    }
    else if(ui->btnPantilt->hasFocus())
    {
        on_btnPantilt_pressed();
        btnPantilt_selected();
    }
    else if(ui->btnMedia->hasFocus())
    {
        on_btnMedia_pressed();
        btnMedia_selected();

        openMediaBrowser();
    }
    else if(ui->btnTasks->hasFocus())
    {
        on_btnTasks_pressed();
        btnTasks_selected();
        openTasksWin();
    }
    else if(ui->btnNuc->hasFocus())
    {
        on_btnNuc_pressed();
        btnNuc_selected();
    }
    else if(ui->btnZoom->hasFocus())
    {
        on_btnZoom_pressed();
        btnZoom_selected();
    }
    else if(ui->btnPolarity->hasFocus())
    {
        on_btnPolarity_pressed();
        btnPolarity_selected();
    }
    else if(ui->btnMenu->hasFocus())
    {
        on_btnMenu_pressed();
        btnMenu_selected();
        openMenuWin();
    }
    else if(ui->btnScreenshot->hasFocus())
    {
        on_btnScreenshot_pressed();
        btnScreenshot_selected();
        makeScreenshot();
    }
    else if(ui->btnExpand->hasFocus())
    {
        on_btnExpand_pressed();
        btnExpand_selected();
        openExpandedWin();
    }
}

void MainWindow::gpioBtnLeft()
{
    if(ui->btnNuc->hasFocus())
    {
        btnNuc_released();
        ui->btnLRF->setFocus();
        btnLrf_selected();
    }
    else if(ui->btnZoom->hasFocus())
    {
        btnZoom_released();
        ui->btnDayir->setFocus();
        btnDayir_selected();
    }
    else if(ui->btnPolarity->hasFocus())
    {
        if(day_ir == false)
        {
            if(polarity_day == true)
            {
                btnPolarity_pressed();
            }
            else if(polarity_day == false)
            {
                btnPolarity_released();
            }
        }
        else if(day_ir == true)
        {
            if(polarity_ir == true)
            {
                btnPolarity_pressed();
            }
            else if(polarity_ir == false)
            {
                btnPolarity_released();
            }
        }
        ui->btnPantilt->setFocus();
        btnPantilt_selected();
    }
    else if(ui->btnMenu->hasFocus())
    {
        btnMenu_released();
        ui->btnMedia->setFocus();
        btnMedia_selected();
    }
    else if(ui->btnScreenshot->hasFocus())
    {
        btnScreenshot_released();
        ui->btnExpand->setFocus();
        btnExpand_selected();
    }
    else if(ui->btnExpand->hasFocus())
    {
        btnExpand_released();
        ui->btnTasks->setFocus();
        btnTasks_selected();
    }
}

void MainWindow::gpioBtnRight()
{
    if(ui->btnLRF->hasFocus())
    {
        btnLrf_released();
        if(ui->btnNuc->isEnabled())
        {
            ui->btnNuc->setFocus();
            btnNuc_selected();
        }
        else
        {
            ui->btnZoom->setFocus();
            btnZoom_selected();
        }
    }
    else if(ui->btnDayir->hasFocus())
    {
        if(day_ir == true)
        {
            btnDayir_pressed();
            ui->btnZoom->setFocus();
            btnZoom_selected();
        }
        else
        {
            btnDayir_released();
            ui->btnZoom->setFocus();
            btnZoom_selected();
        }
    }
    else if(ui->btnPantilt->hasFocus())
    {
        btnPantilt_released();
        ui->btnPolarity->setFocus();
        btnPolarity_selected();
    }
    else if(ui->btnMedia->hasFocus())
    {
        btnMedia_released();
        ui->btnMenu->setFocus();
        btnMenu_selected();
    }
    else if(ui->btnTasks->hasFocus())
    {
        btnTasks_released();
        ui->btnExpand->setFocus();
        btnExpand_selected();
    }
    else if(ui->btnExpand->hasFocus())
    {
        btnExpand_released();
        ui->btnScreenshot->setFocus();
        btnScreenshot_selected();
    }
}

void MainWindow::gpioBtnUp()
{
    if(ui->btnTasks->hasFocus())
    {
        btnTasks_released();
        ui->btnMedia->setFocus();
        btnMedia_selected();
    }
    else if(ui->btnMedia->hasFocus())
    {
        btnMedia_released();
        ui->btnPantilt->setFocus();
        btnPantilt_selected();
    }
    else if(ui->btnPantilt->hasFocus())
    {
        if(pantilt_ == true)
        {
            btnPantilt_pressed();
            ui->btnDayir->setFocus();
            btnDayir_selected();
        }
        else
        {
            btnPantilt_released();
            ui->btnDayir->setFocus();
            btnDayir_selected();
        }
    }
    else if(ui->btnDayir->hasFocus())
    {
        if(day_ir == true)
        {
            btnDayir_pressed();
            ui->btnLRF->setFocus();
            btnLrf_selected();
        }
        else
        {
            btnDayir_released();
            ui->btnLRF->setFocus();
            btnLrf_selected();
        }
    }
    else if(ui->btnScreenshot->hasFocus())
    {
        btnScreenshot_released();
        ui->btnMenu->setFocus();
        btnMenu_selected();
    }
    else if(ui->btnMenu->hasFocus())
    {
        btnMenu_released();
        ui->btnPolarity->setFocus();
        btnPolarity_selected();
    }
    else if(ui->btnPolarity->hasFocus())
    {
        if(day_ir == false)
        {
            if(polarity_day == true)
            {
                btnPolarity_pressed();
            }
            else if(polarity_day == false)
            {
                btnPolarity_released();
            }
        }
        else if(day_ir == true)
        {
            if(polarity_ir == true)
            {
                btnPolarity_pressed();
            }
            else if(polarity_ir == false)
            {
                btnPolarity_released();
            }
        }
        ui->btnZoom->setFocus();
        btnZoom_selected();
    }
    else if(ui->btnZoom->hasFocus())
    {
        if(ui->btnNuc->isEnabled())
        {
            btnZoom_released();
            ui->btnNuc->setFocus();
            btnNuc_selected();
        }
    }
}

void MainWindow::gpioBtnDown()
{
    if(ui->btnLRF->hasFocus())
    {
        btnLrf_released();
        ui->btnDayir->setFocus();
        btnDayir_selected();
    }
    else if(ui->btnDayir->hasFocus())
    {
        if(day_ir == true)
        {
            btnDayir_pressed();
            ui->btnPantilt->setFocus();
            btnPantilt_selected();
        }
        else
        {
            btnDayir_released();
            ui->btnPantilt->setFocus();
            btnPantilt_selected();
        }
    }
    else if(ui->btnPantilt->hasFocus())
    {
        if(pantilt_ == true)
        {
            btnPantilt_pressed();
            ui->btnMedia->setFocus();
            btnMedia_selected();
        }
        else
        {
            btnPantilt_released();
            ui->btnMedia->setFocus();
            btnMedia_selected();
        }
    }
    else if(ui->btnMedia->hasFocus())
    {
        btnMedia_released();
        ui->btnTasks->setFocus();
        btnTasks_selected();
    }
    else if(ui->btnNuc->hasFocus())
    {
        btnNuc_released();
        ui->btnZoom->setFocus();
        btnZoom_selected();
    }
    else if(ui->btnZoom->hasFocus())
    {
        btnZoom_released();
        ui->btnPolarity->setFocus();
        btnPolarity_selected();
    }
    else if(ui->btnPolarity->hasFocus())
    {
        if(day_ir == false)
        {
            if(polarity_day == true)
            {
                btnPolarity_pressed();
            }
            else if(polarity_day == false)
            {
                btnPolarity_released();
            }
        }
        else if(day_ir == true)
        {
            if(polarity_ir == true)
            {
                btnPolarity_pressed();
            }
            else if(polarity_ir == false)
            {
                btnPolarity_released();
            }
        }
        ui->btnMenu->setFocus();
        btnMenu_selected();
    }
    else if(ui->btnMenu->hasFocus())
    {
        btnMenu_released();
        ui->btnScreenshot->setFocus();
        btnScreenshot_selected();
    }
}

void MainWindow::gpioBtnZoom()
{
    //changeZoom();
    ui->btnZoom->setFocus();
    on_btnZoom_pressed();
    btnZoom_selected();
}

void MainWindow::gpioBtnLrf()
{
    ui->btnLRF->setFocus();
    on_btnLRF_pressed();
    btnLrf_selected();
}

void MainWindow::gpioBtnPantiltUpPressed()
{
    on_btnPantilt_up_pressed();
}

void MainWindow::gpioBtnPantiltDownPressed()
{
    on_btnPantilt_down_pressed();
}

void MainWindow::gpioBtnPantiltLeftPressed()
{
    on_btnPantilt_left_pressed();
}

void MainWindow::gpioBtnPantiltRightPressed()
{
    on_btnPantilt_right_pressed();
}

void MainWindow::gpioBtnPantiltUpReleased()
{
    on_btnPantilt_up_released();
}

void MainWindow::gpioBtnPantiltDownReleased()
{
    on_btnPantilt_down_released();
}

void MainWindow::gpioBtnPantiltLeftReleased()
{
    on_btnPantilt_left_released();
}

void MainWindow::gpioBtnPantiltRightReleased()
{
    on_btnPantilt_right_released();
}

void MainWindow::checkIrZoom()
{
    setIconPixmap();

    if(ir_zoom == "1X")
    {
        hikVision->makeZoom(2);
        ui->btnZoom->setIcon(*zoom2x);
        ir_zoom = "2X";
    }
    else if(ir_zoom == "2X")
    {
        hikVision->makeZoom(3);
        ui->btnZoom->setIcon(*zoom4x);
        ir_zoom = "4X";
    }
    else if (ir_zoom == "4X")
    {
        hikVision->makeZoom(4);
        ui->btnZoom->setIcon(*zoom8x);
        ir_zoom = "8X";
    }
    else if (ir_zoom == "8X")
    {
        hikVision->makeZoom(1);
        ui->btnZoom->setIcon(*zoom1x);
        ir_zoom = "1X";
    }
}


void MainWindow::checkDayZoom()
{
    setIconPixmap();

    if(day_zoom == "1X")
    {
        SetZoomDayCam(2);
        ui->btnZoom->setIcon(*zoom2x);
        day_zoom = "2X";
    }
    else if(day_zoom == "2X")
    {
        SetZoomDayCam(4);
        ui->btnZoom->setIcon(*zoom4x);
        day_zoom = "4X";
    }
    else if (day_zoom == "4X")
    {
        SetZoomDayCam(8);
        ui->btnZoom->setIcon(*zoom8x);
        day_zoom = "8X";
    }
    else if (day_zoom == "8X")
    {
        SetZoomDayCam(16);
        ui->btnZoom->setIcon(*zoom16x);
        day_zoom = "16X";
    }
    else if (day_zoom == "16X")
    {
        SetZoomDayCam(1);
        ui->btnZoom->setIcon(*zoom1x);
        day_zoom = "1X";
    }
}

void MainWindow::updateCoordParameters()
{
    QString cs, ct, pm_z;

    if(coordinate_system == "wgs")
    {
        cs = "NATO(WGS84)";
        if(coordinate_type == "utm")
        {
            ct = "UTM";
            if(zone == "35")
            {
                pm_z = "35";
            }
            else if(zone == "34")
            {
                pm_z = "34";
            }
        }
        else if(coordinate_type == "bl")
        {
            ct = "B,L";
            pm_z = "";
        }
    }
    else if(coordinate_system == "krasovsky")
    {
        cs = "Krasovsky(1942/83)";
        if(coordinate_type == "xy")
        {
            ct = "X,Y";
            if(zone == "27")
            {
                pm_z = "27";
            }
            else if(zone == "21")
            {
                pm_z = "21";
            }
        }
        else if(coordinate_type == "bl")
        {
            ct = "B,L";
            pm_z = "";
        }
    }

    ui->coordInfo->setText("   " + cs + "   " + ct + "   " + pm_z);
}


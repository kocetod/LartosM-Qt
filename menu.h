#ifndef MENU_H
#define MENU_H

#include "mainwindow.h"
#include <QDialog>
#include <QStandardItemModel>
#include "LartosPointObj.h"
#include "SaveLartosPoints.h"
#include "SaveLartosUserData.h"


namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

    void switchToBG();

    void switchToEN();

    void InitKey(QString position, QString style, int btnFontSize, int labFontSize);

    void gpioBtnOk();

    void gpioBtnLeft();

    void gpioBtnRight();

    void gpioBtnUp();

    void gpioBtnDown();

    void readAllUserSettings();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void changeUserPassword();

    void setCoordinateSystemParameters();

    void checkCoordinateSystem();
    void checkPointsCoordinateType();

    void updateFrame(const QPixmap &frame);

    void keyboardInput_m();
    void btnConfirmPass_pressed();
    void btnConfirmPass_released();
    void btnChooseLang_pressed();
    void btnChooseLang_released();
    void btnBack_pressed();
    void btnBack_released();
    void m_confirmPass_pressed();
    void m_confirmPass_released();
    void m_ok_pressed();
    void m_ok_released();
    void m_back_pressed();
    void m_back_released();
    void btnChooseCoordSys_pressed();
    void btnChooseCoordSys_released();
    void up_pressed();
    void up_released();
    void down_pressed();
    void down_released();
    void left_pressed();
    void left_released();
    void right_pressed();
    void right_released();
    void btnConfirmDecl_pressed();
    void btnConfirmDecl_released();
    void k1_pressed();
    void k1_released();
    void k2_pressed();
    void k2_released();
    void k3_pressed();
    void k3_released();
    void k4_pressed();
    void k4_released();
    void k5_pressed();
    void k5_released();
    void k6_pressed();
    void k6_released();
    void k7_pressed();
    void k7_released();
    void k8_pressed();
    void k8_released();
    void k9_pressed();
    void k9_released();
    void k0_pressed();
    void k0_released();
    void ok_pressed();
    void ok_released();
    void del_pressed();
    void del_released();
    void k1_magneticDeclination_pressed();
    void k1_magneticDeclination_released();
    void k2_magneticDeclination_pressed();
    void k2_magneticDeclination_released();
    void k3_magneticDeclination_pressed();
    void k3_magneticDeclination_released();
    void k4_magneticDeclination_pressed();
    void k4_magneticDeclination_released();
    void k5_magneticDeclination_pressed();
    void k5_magneticDeclination_released();
    void k6_magneticDeclination_pressed();
    void k6_magneticDeclination_released();
    void k7_magneticDeclination_pressed();
    void k7_magneticDeclination_released();
    void k8_magneticDeclination_pressed();
    void k8_magneticDeclination_released();
    void k9_magneticDeclination_pressed();
    void k9_magneticDeclination_released();
    void k0_magneticDeclination_pressed();
    void k0_magneticDeclination_released();
    void k_minus_magneticDeclination_pressed();
    void k_minus_magneticDeclination_released();
    void k_plus_magneticDeclination_pressed();
    void k_plus_magneticDeclination_released();
    void k_dot_magneticDeclination_pressed();
    void k_dot_magneticDeclination_released();
    void k_del_magneticDeclination_pressed();
    void k_del_magneticDeclination_released();
    void ok_reset_pressed();
    void ok_reset_released();
    void btnConfirmPassReset_pressed();
    void btnConfirmPassReset_released();
    void btnReset_pressed();
    void btnReset_released();

    void btnConfirmPass_selected();
    void btnChooseLang_selected();
    void btnBack_selected();
    void btnChooseCoordSys_selected();
    void btnConfirmDecl_selected();
    void k1_selected();
    void k2_selected();
    void k3_selected();
    void k4_selected();
    void k5_selected();
    void k6_selected();
    void k7_selected();
    void k8_selected();
    void k9_selected();
    void k0_selected();
    void ok_selected();
    void del_selected();
    void k1_magneticDeclination_selected();
    void k2_magneticDeclination_selected();
    void k3_magneticDeclination_selected();
    void k4_magneticDeclination_selected();
    void k5_magneticDeclination_selected();
    void k6_magneticDeclination_selected();
    void k7_magneticDeclination_selected();
    void k8_magneticDeclination_selected();
    void k9_magneticDeclination_selected();
    void k0_magneticDeclination_selected();
    void k_minus_magneticDeclination_selected();
    void k_plus_magneticDeclination_selected();
    void k_dot_magneticDeclination_selected();
    void k_del_magneticDeclination_selected();
    void btnConfirmPassReset_selected();
    void btnReset_selected();

    void setWgsStyleSheet();
    void setKrasovskyStyleSheet();
    void setUtmStyleSheet();
    void setDlhStyleSheet();
    void setZone1StyleSheet();
    void setZone2StyleSheet();

    void releaseAll();

    void showKeyboard();

    void hideKeyboard();

    void moveLeft();

    void moveRight();

    void showWrongM();

    void hideWrongM();

    void moveLeftM();

    void moveRightM();

    void showKeyboardM();

    void hideKeyboardM();

    void showManufacturing();

    void hideManufacturing();

    void on_btnConfirmPass_pressed();

    void on_btnConfirmPass_released();

    void on_btnChooseLang_pressed();

    void on_btnChooseLang_released();

    void on_btnBack_pressed();

    void on_btnBack_released();

    void on_btnBG_pressed();

    void on_btnEN_pressed();

    void on_brightness_sliderMoved(int position);

    void on_contrast_sliderMoved(int position);

    void on_dde_sliderMoved(int position);

    void on_k1_pressed();

    void on_k1_released();

    void on_k2_pressed();

    void on_k2_released();

    void on_k3_pressed();

    void on_k3_released();

    void on_k4_pressed();

    void on_k4_released();

    void on_k5_pressed();

    void on_k5_released();

    void on_k6_pressed();

    void on_k6_released();

    void on_k7_pressed();

    void on_k7_released();

    void on_k8_pressed();

    void on_k8_released();

    void on_k9_pressed();

    void on_k9_released();

    void on_k0_pressed();

      void on_k0_released();

      void on_ok_pressed();

      void on_ok_released();

      void on_del_pressed();

      void on_del_released();

      void keyboardInput();

      void deleteLast();

      void restoreToolBox();

      void expandToolBox();

      void restoreToolBoxM();

      void expandToolBoxM();

      void showMenu();

      void hideMenu();

      void checkMPass();

      void on_m_confirmPass_pressed();

      void on_m_confirmPass_released();

      void on_m_ok_pressed();

      void on_hide_pressed();

      void on_m_back_pressed();

      void on_m_back_released();

      void on_settings_currentChanged(int index);

      void on_btnChooseCoordSys_pressed();

      void on_btnChooseCoordSys_released();

      void on_up_pressed();

      void on_up_released();

      void on_down_pressed();

      void on_down_released();

      void on_left_pressed();

      void on_left_released();

      void on_right_pressed();

      void on_right_released();

      void on_k1_magneticDeclination_pressed();

      void on_k1_magneticDeclination_released();

      void on_k2_magneticDeclination_pressed();

      void on_k2_magneticDeclination_released();

      void on_k3_magneticDeclination_pressed();

      void on_k3_magneticDeclination_released();

      void on_k4_magneticDeclination_pressed();

      void on_k4_magneticDeclination_released();

      void on_k5_magneticDeclination_pressed();

      void on_k5_magneticDeclination_released();

      void on_k6_magneticDeclination_pressed();

      void on_k6_magneticDeclination_released();

      void on_k7_magneticDeclination_pressed();

      void on_k7_magneticDeclination_released();

      void on_k8_magneticDeclination_pressed();

      void on_k8_magneticDeclination_released();

      void on_k9_magneticDeclination_pressed();

      void on_k9_magneticDeclination_released();

      void on_k0_magneticDeclination_pressed();

      void on_k0_magneticDeclination_released();

      void on_k_minus_magneticDeclination_pressed();

      void on_k_minus_magneticDeclination_released();

      void on_k_plus_magneticDeclination_pressed();

      void on_k_plus_magneticDeclination_released();

      void on_k_dot_magneticDeclination_pressed();

      void on_k_dot_magneticDeclination_released();

      void on_k_del_magneticDeclination_pressed();

      void on_k_del_magneticDeclination_released();

      void on_btnConfirmDecl_pressed();

      void on_btnConfirmDecl_released();

      void on_btnConfirmPassReset_pressed();

      void on_btnConfirmPassReset_released();

      void on_btnReset_pressed();

      void on_btnReset_released();

    void on_ok_reset_pressed();

    void on_ok_reset_released();

    void on_wgs_pressed();

    void on_krasovsky_pressed();

    void on_btnConfirmCamSettings_pressed();

    void on_btnConfirmCamSettings_released();

    void on_dde_mode_stateChanged(int arg1);


    void on_btna_pressed();
    void on_btnb_pressed();
    void on_btnc_pressed();
    void on_btnd_pressed();
    void on_btne_pressed();
    void on_btnf_pressed();
    void on_btng_pressed();
    void on_btnh_pressed();
    void on_btni_pressed();
    void on_btnj_pressed();
    void on_btnk_pressed();
    void on_btnl_pressed();
    void on_btnm_pressed();
    void on_btnn_pressed();
    void on_btno_pressed();
    void on_btnp_pressed();
    void on_btnq_pressed();
    void on_btnr_pressed();
    void on_btns_pressed();
    void on_btnt_pressed();
    void on_btnu_pressed();
    void on_btnv_pressed();
    void on_btnw_pressed();
    void on_btnx_pressed();
    void on_btny_pressed();
    void on_btnz_pressed();

    void on_btn_Sym1_pressed();
    void on_btn_Sym2_pressed();
    void on_btn_Sym3_pressed();
    void on_btn_Sym4_pressed();
    void on_btn_Sym5_pressed();
    void on_btn_Sym6_pressed();
    void on_btn_Sym7_pressed();
    void on_btn_Sym8_pressed();
    void on_btn_Sym9_pressed();
    void on_btn_Sym10_pressed();
    void on_btn_Sym11_pressed();
    void on_btn_Sym12_pressed();
    void on_btn_Sym13_pressed();
    void on_btn_Sym14_pressed();
    void on_btn_Sym15_pressed();
    void on_btn_Sym16_pressed();
    void on_btn_Sym17_pressed();
    void on_btn_Sym18_pressed();
    void on_btn_Sym19_pressed();
    void on_btn_Sym20_pressed();
    void on_btn_Sym21_pressed();

    void on_btn0_pressed();
    void on_btn00_pressed();
    void on_btn1_pressed();
    void on_btn2_pressed();
    void on_btn3_pressed();
    void on_btn4_pressed();
    void on_btn5_pressed();
    void on_btn6_pressed();
    void on_btn7_pressed();
    void on_btn8_pressed();
    void on_btn9_pressed();
    void on_btnDot_pressed();

    void btnOkDecl_pressed();
    void btnOkDecl_released();
    void btnOkDecl_selected();

    void btnAdd_selected();
    void btnDelete_selected();
    void btnAdd_pressed();
    void btnAdd_released();
    void btnDelete_pressed();
    void btnDelete_released();

    void on_btn_Space_pressed();

    void on_btn_Enter_pressed();

    void on_btn_capslock_pressed();

    void on_btn_backspace_pressed();

    void on_add_btn_pressed();

    void on_delete_btn_released();

    void on_add_btn_released();

    void on_delete_btn_pressed(); 

    void on_point_listView_clicked(const QModelIndex &index);

    void on_btnOkDecl_pressed();

    void on_btnOkDecl_released();

    void on_utm_xy_pressed();

    void on_bl_pressed();

    void on_zone_35_pressed();

    void on_zone_34_pressed();

    void on_btnOk_pressed();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_btnSaveReticlePos_pressed();

    void on_btnSaveReticlePos_released();

    void on_btnCenterReticle_pressed();

    void on_btnShowOffsetCorrectionReticle_pressed();

    void on_btnShowOffsetCorrectionReticle_released();

private:
    Ui::Menu *ui;

    QString keyboard();
    void addLetter(QString letter);
    void removeLetter();
    void setCapLetters();
    void setSmallLetters();
    void addPoints(QString name, QString lattitude, QString longitude, QString altitude, QString type);
    void initTableView();
    void loadPointData();
    void removePoint(QString index);
    void showDataInTableView(LartosPointObj point);

  LartosPointObj pointObj;
  SaveLartosPoint *savePointObj;
  QStandardItemModel *model;
  QStringList horizontalHeader;
  QStringList verticalHeader;
  QString inputValue;
  bool capsLock;
  QString pointForDelete;
  QHash<QString,LartosPointObj> hashPoint;
  SaveLartosUserData  *saveuserdata;
};

#endif // MENU_H

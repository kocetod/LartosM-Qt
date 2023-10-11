#pragma once
#include <QFile>
#include <QFileInfoList>
#include <QWidget>
#include "usbdevice.h"

#ifndef MEDIABROWSER_H
#define MEDIABROWSER_H

#include <QDialog>
#include <QDir>
#include <QFileSystemModel>

namespace Ui {
class MediaBrowser;
}

class MediaBrowser : public QDialog
{
    Q_OBJECT

public:
    explicit MediaBrowser(QWidget *parent = nullptr);
    ~MediaBrowser();

    void switchToBG();

    void switchToEN();

    void btnCopy_pressed();

    void btnCopy_released();

    void btnCopy_selected();

    void btnCopyAll_pressed();

    void btnCopyAll_released();

    void btnCopyAll_selected();

    void btnBack_pressed();

    void btnBack_released();

    void btnBack_selected();

    void selectPrevious();

    void selectNext();

    void showSelected();

    void listFiles();

    QString directory = "/LartosImages";

    QDir pathToDir;

    void gpioBtnOk();

    void gpioBtnLeft();

    void gpioBtnRight();

private slots:
    void on_imageBrowser_clicked(const QModelIndex &index);

    void on_btnCopy_pressed();

    void on_btnCopy_released();

    void on_btnBack_pressed();

    void on_btnBack_released();

    void on_imageBrowser_pressed(const QModelIndex &index);

    void on_btnCopyAll_pressed();

    void on_btnCopyAll_released();

private:
    Ui::MediaBrowser *ui;

    QHash<int, UsbDevice> usbDevices;

    QFileSystemModel *listModel;

    bool listSelected;

    void openImageFile();

    void copyToFlashDrive();

    void mountFlashDrive();

    void scanForFlashDrive();

    void createFolderOnUsbDevice();

    void createMediaDirectory();

    QFileInfoList listFilesInfo;

    int indexOfSelectedImage;

    void messageBox(QString title, QString text);

    void waitMessage();

    void copyAllToFlashDrive();
};

#endif // MEDIABROWSER_H

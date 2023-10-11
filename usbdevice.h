#ifndef USBDEVICE_H
#define USBDEVICE_H

#include <QString>

class UsbDevice
{
public:
    UsbDevice();

    void setDeviceName(QString deviceName);

    void setDeviceFileSystem(QString deviceFileSystem);

    void setDevicePath(QString devicePath);

    void setDeviceSize(QString deviceSize);

    void setDeviceFreeSize(QString deviceFreeSize);

    void setReadOnly(bool isReadOnly);

    QString getDeviceName();

    QString getDeviceFileSystem();

    QString getDevicePath();

    QString getDeviceSize();

    QString getDeviceFreeSize();

    bool getReadOnly();

private:
    QString deviceName;
    QString deviceFileSystem;
    QString devicePath;
    QString deviceSize;
    QString deviceFreeSize;
    bool isReadOnly;
};

#endif // USBDEVICE_H

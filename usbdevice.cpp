#include "usbdevice.h"

UsbDevice::UsbDevice()
{

}

void UsbDevice::setDeviceName(QString deviceName){
    this->deviceName = deviceName;
}

void UsbDevice::setDeviceFileSystem(QString deviceFileSystem){
    this->deviceFileSystem = deviceFileSystem;
}

void UsbDevice::setDevicePath(QString devicePath){
    this->devicePath = devicePath;
}

void UsbDevice::setDeviceSize(QString deviceSize){
    this->deviceSize = deviceSize;
}

void UsbDevice::setDeviceFreeSize(QString deviceFreeSize){
    this->deviceFreeSize = deviceFreeSize;
}

void UsbDevice::setReadOnly(bool isReadOnly){
    this->isReadOnly = isReadOnly;
}

QString UsbDevice::getDeviceName(){
    return this->deviceName;
}

QString UsbDevice::getDeviceFileSystem(){
    return this->deviceFileSystem;
}

QString UsbDevice::getDevicePath(){
    return this->devicePath;
}

QString UsbDevice::getDeviceSize(){
    return this->deviceSize;
}

QString UsbDevice::getDeviceFreeSize(){
    return this->deviceFreeSize;
}

bool UsbDevice::getReadOnly(){
    return this->isReadOnly;
}

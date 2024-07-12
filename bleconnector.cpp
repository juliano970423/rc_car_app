#include "bleconnector.h"
#include <iostream>
BleConnector::BleConnector(QObject *parent) : QObject(parent), controller(nullptr), service(nullptr) {}

void BleConnector::connectToDevice(const QBluetoothDeviceInfo &deviceInfo) {
    // 创建新的控制器对象
    controller = QLowEnergyController::createCentral(deviceInfo, this);
    // 连接到控制器的信号
    connect(controller, &QLowEnergyController::connected, this, &BleConnector::handleConnected);
    connect(controller, &QLowEnergyController::disconnected, this, &BleConnector::handleDisconnected);
    connect(controller, &QLowEnergyController::errorOccurred, this, &BleConnector::handleOccurError);

    // 连接到设备
    controller->connectToDevice();
}

void BleConnector::sendData(const QByteArray &data) {
    // 发送数据（你需要在实际应用中实现这个函数）

    QLowEnergyCharacteristic characteristic = service->characteristic(QBluetoothUuid(quint16(0xFFE1)));
    if (!characteristic.isValid()) {
        std::cout << "Characteristic not valid" << std::endl;
        return;
    }
    QByteArray dataToSend = data;
    //dataToSend.prepend('\r');
    dataToSend.append('\n');
    service->writeCharacteristic(characteristic, dataToSend);

}

void BleConnector::handleConnected() {
    //std::cout<<controller->remoteDeviceUuid().toString().toStdString()<<std::endl;
    controller->discoverServices();

    QList<QBluetoothUuid> serviceUuids = controller->services();
    foreach (const QBluetoothUuid &uuid, serviceUuids) {
        std::cout <<"service uuids"<< uuid.toString().toStdString()<<std::endl;
    }
    service = controller->createServiceObject(QBluetoothUuid(quint16(0xFFE0)), this);
    service->discoverDetails();
    if (!service) {
            std::cout << "Service is not valid"<<std::endl;
        return;
    }
        emit connected();
    }
void BleConnector::handleDisconnected() {
        emit disconnected();
}
void BleConnector::handleOccurError(QLowEnergyController::Error error){
    emit errorOccurred(error);
}


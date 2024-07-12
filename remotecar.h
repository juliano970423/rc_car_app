#ifndef REMOTECAR_H
#define REMOTECAR_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QDebug>
#include <iostream>

#include "bledevicescanner.h"
#include "bleconnector.h"

class RemoteCar : public QObject
{
    Q_OBJECT

public:
    QString bt_name;
    BleConnector connector;
    QBluetoothDeviceInfo bt_info;
    explicit RemoteCar(QObject *parent = nullptr);
public slots:
    void receiveMessage(const QString &message){
        std::cout<<message.toStdString()<<std::endl;
        connector.sendData(message.toLocal8Bit());

    }
    void connect_to_BT(const QString &bt_name_inputed){
        emit updateConnectingState("scanning");
        std::cout<<"bt_name "<<bt_name_inputed.toStdString()<<std::endl;
        bt_name=bt_name_inputed;
        BLEDeviceScanner *scanner = new BLEDeviceScanner(this); // 'this' 是父对象
        connect(scanner, &BLEDeviceScanner::deviceDiscovered, this, &RemoteCar::handleDeviceDiscovered);
        connect(scanner, &BLEDeviceScanner::deviceScanError, this, &RemoteCar::handleDeviceScanError);
        connect(scanner, &BLEDeviceScanner::deviceScanFinished, this, &RemoteCar::handleDeviceScanFinished);
        scanner->startScanning();
    }
    void handleDeviceDiscovered(const QBluetoothDeviceInfo &info){
        //std::cout<<info.name().toStdString()<<std::endl;
        if (info.name()==bt_name){
            emit updateConnectingState("connecting");

            std::cout<<info.name().toStdString()<<std::endl;
            bt_info = info;

            QObject::connect(&connector, &BleConnector::connected, [&]{
                //qDebug() << "Connected to device:" << deviceName;
                std::cout<<"connected"<<std::endl;
                emit updateConnectingState("connected");
                // 连接到设备后可以执行其他操作
            });
            QObject::connect(&connector, &BleConnector::disconnected, [&]{
                //qDebug() << "Disconnected from device";
                // 断开连接后的处理
                emit updateConnectingState("disconnected");
                std::cout<<"disconnected"<<std::endl;
            });
            QObject::connect(&connector, &BleConnector::errorOccurred, [&](const QLowEnergyController::Error &error){
                std::cout << "Error:" << static_cast<int>(error)<<std::endl;
                emit updateConnectingState("connect error");
                // 错误处理
            });
            connector.connectToDevice(bt_info);
        }

    }
    void handleDeviceScanError(const QString &error){

    }
    void handleDeviceScanFinished(){
        std::cout<<"Finished"<<std::endl;
    }

signals:
    void updateConnectingState(QString state);
};

#endif // REMOTECAR_H

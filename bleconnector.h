#ifndef BLEBLECONNECTOR_H
#define BLEBLECONNECTOR_H
#include <QLowEnergyController>
#include <QBluetoothDeviceInfo>
#include <QObject>

class BleConnector : public QObject
{
    Q_OBJECT

public:
    explicit BleConnector(QObject *parent = nullptr);

    void connectToDevice(const QBluetoothDeviceInfo &deviceInfo);
    void sendData(const QByteArray &data);

signals:
    void connected();
    void disconnected();
    void errorOccurred(QLowEnergyController::Error &errorMessage);

private slots:
    void handleConnected();
    void handleDisconnected();
    void handleOccurError(QLowEnergyController::Error error);


private:
    QLowEnergyController *controller;
    QLowEnergyService *service;
};



#endif // BLECONNECTOR_H

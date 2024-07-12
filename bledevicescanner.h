#ifndef BLEDEVICESCANNER_H
#define BLEDEVICESCANNER_H

#include <QObject>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>

class BLEDeviceScanner : public QObject
{
    Q_OBJECT
public:
    explicit BLEDeviceScanner(QObject *parent = nullptr);
    ~BLEDeviceScanner();

    void startScanning(); // 啟動設備掃描

signals:
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void deviceScanError(const QString &error);
    void deviceScanFinished();

private:
    QBluetoothDeviceDiscoveryAgent *m_discoveryAgent;

private slots:
    void addDevice(const QBluetoothDeviceInfo &info);
    void scanError(QBluetoothDeviceDiscoveryAgent::Error error);
    void scanFinished();
};

#endif // BLEDEVICESCANNER_H

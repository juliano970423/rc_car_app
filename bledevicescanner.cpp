#include "bledevicescanner.h"
#include <iostream>

BLEDeviceScanner::BLEDeviceScanner(QObject *parent) : QObject(parent)
{
    m_discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_discoveryAgent->setLowEnergyDiscoveryTimeout(15000);
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BLEDeviceScanner::addDevice  );
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
            this, &BLEDeviceScanner::scanError);
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &BLEDeviceScanner::scanFinished);

}

BLEDeviceScanner::~BLEDeviceScanner()
{
    delete m_discoveryAgent;
}

void BLEDeviceScanner::startScanning()
{
    m_discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BLEDeviceScanner::addDevice(const QBluetoothDeviceInfo &info)
{
    // 處理發現的設備信息，例如打印設備名稱、地址等
    emit deviceDiscovered(info);
}

void BLEDeviceScanner::scanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    // 處理掃描錯誤
    emit deviceScanError(m_discoveryAgent->errorString());
}

void BLEDeviceScanner::scanFinished()
{
    // 掃描完成
    emit deviceScanFinished();
}

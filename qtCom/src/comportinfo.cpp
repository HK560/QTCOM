#include "include/comportinfo.h"
using namespace MCOMINFO;

comPortInfo::comPortInfo() {}

comPortInfo::~comPortInfo() { delete portInfo; }

QStringList comPortInfo::GetComPortInfo() {
    portList = QSerialPortInfo::availablePorts();
    QStringList portInfoStringList;
    portInfo->clear();

    for (QList<QSerialPortInfo>::iterator i = portList.begin();
         i != portList.end(); i++) {
        portInfoStringList.append(i->portName());
        portInfo->append(qMakePair(i->portName(), *i));
        qDebug() << i->portName();
    }
    return portInfoStringList;
}

const QMap<QString, QSerialPort::BaudRate> comPortInfo::baudInfo = {
    {"1200", QSerialPort::Baud1200},   {"2400", QSerialPort::Baud2400},
    {"4800", QSerialPort::Baud4800},   {"9600", QSerialPort::Baud9600},
    {"19200", QSerialPort::Baud19200}, {"38400", QSerialPort::Baud38400},
    {"57600", QSerialPort::Baud57600}, {"115200", QSerialPort::Baud115200}};

QStringList comPortInfo::GetCombaudInfo() {
    QStringList baudInfoList;
    for (QMap<QString, QSerialPort::BaudRate>::const_iterator i =
             baudInfo.begin();
         i != baudInfo.end(); i++) {
        baudInfoList.append(i.key());
    }
    qSort(baudInfoList.begin(), baudInfoList.end(),
          [](const QString &A, const QString &B) {
              return A.toInt() < B.toInt();
          });
    return baudInfoList;
}
QVector<QPair<QString, QSerialPortInfo>> *comPortInfo::portInfo =
    new QVector<QPair<QString, QSerialPortInfo>>();

QList<QSerialPortInfo> comPortInfo::portList;

const QMap<QString, QSerialPort::DataBits> comPortInfo::dataBitsInfo = {
    {"8", QSerialPort::Data8},
    {"7", QSerialPort::Data7},
    {"6", QSerialPort::Data6},
    {"5", QSerialPort::Data5}};

const QStringList comPortInfo::dataBitsStrList = 
    {"8", "7", "6", "5"};

const QMap<QString, QSerialPort::FlowControl> comPortInfo::flowControlInfo = {
    {tr("无"), QSerialPort::NoFlowControl},
    {tr("硬件控制"), QSerialPort::HardwareControl},
    {tr("软件控制"), QSerialPort::SoftwareControl}};

const QStringList comPortInfo::flowControlStrList = 
    {tr("无"), tr("硬件控制"),tr("软件控制")};

const QMap<QString, QSerialPort::Parity> comPortInfo::parityInfo = {
    {tr("无"), QSerialPort::NoParity},
    {"Even", QSerialPort::EvenParity},
    {"Odd", QSerialPort::OddParity},
    {"Space", QSerialPort::SpaceParity},
    {"Mark", QSerialPort::MarkParity}};

const QStringList comPortInfo::parityStrList = 
    {tr("无"), "Even", "Odd","Space", "Mark"};

const QMap<QString, QSerialPort::StopBits> comPortInfo::stopBitsInfo = {
    {"1", QSerialPort::OneStop},
    {"1.5", QSerialPort::OneAndHalfStop},
    {"2", QSerialPort::TwoStop}};

const QStringList comPortInfo::stopBitsStrList = 
    {"1", "1.5","2"};
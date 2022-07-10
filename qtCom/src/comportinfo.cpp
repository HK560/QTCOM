#include "comportinfo.h"
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

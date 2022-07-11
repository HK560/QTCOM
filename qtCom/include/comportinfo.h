#ifndef COMPORTINFO_H
#define COMPORTINFO_H
#include <QDebug>
#include <QList>
#include <QPair>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace MCOMINFO {
class comPortInfo : public QObject {
    Q_OBJECT
   private:
    static QList<QSerialPortInfo> portList;  // QSerialPortInfo *serialPortInfo;
    static QVector<QPair<QString, QSerialPortInfo>> *portInfo;
    
   public:
    comPortInfo();
    ~comPortInfo();
    static QStringList GetComPortInfo();
    
    static QStringList GetCombaudInfo();
    static const QMap<QString, QSerialPort::BaudRate> baudInfo;

    static const QMap<QString, QSerialPort::DataBits> dataBitsInfo;
    static const QStringList dataBitsStrList;

    static const QMap<QString, QSerialPort::FlowControl> flowControlInfo;
    static const QStringList flowControlStrList;

    static const QMap<QString, QSerialPort::Parity> parityInfo;
    static const QStringList parityStrList;

    static const QMap<QString, QSerialPort::StopBits> stopBitsInfo;
    static const QStringList stopBitsStrList;
};

}  // namespace MCOMINFO

#endif  // COMPORTINFO_H

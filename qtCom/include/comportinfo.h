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
class comPortInfo   : public QObject{
    Q_OBJECT
   private:
    static QList<QSerialPortInfo> portList;  // QSerialPortInfo *serialPortInfo;
  
    static QVector<QPair<QString, QSerialPortInfo>> *portInfo;

   public:
    comPortInfo();
    ~comPortInfo();
    static const QMap<QString, QSerialPort::BaudRate> baudInfo;
    static QStringList GetComPortInfo();
    static QStringList GetCombaudInfo();
};

}  // namespace MCOMINFO

#endif  // COMPORTINFO_H

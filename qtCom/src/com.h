#ifndef COM_H
#define COM_H

#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTextCodec>

namespace MCOM {

typedef struct {
    QString portName;
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::FlowControl flowControl;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
} SerialPortSetting;

// enum STATE_CODE {
//     PORT_IS_NULL,
//     PORT_IS_ALREADY_OPENED,
//     PORT_IS_ALREADY_CLOSED,

// };
class COM : public QObject {
    Q_OBJECT
   private:
    volatile static bool portReady;

   protected:
    QSerialPort* serialPort;

   public:
    COM();
    ~COM();
    bool SettingPort(const SerialPortSetting& settingStruct);
    bool OpenPort();
    bool ClosePort();
    bool SendMessageToPort(const QString& data);
    bool PortIsReady() { return (portReady && serialPort->isOpen()); }
   public slots:
    void errorHandle(QSerialPort::SerialPortError error);
    private slots:
    void SendDataToMainwindow();
    signals:
    void ReceiveData(const  QByteArray& data);
};

}  // namespace MCOM
#endif  // COM_H

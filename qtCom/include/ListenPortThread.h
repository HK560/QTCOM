// #ifndef LISTENPORTTHREAD_H
// #define LISTENPORTTHREAD_H

// #include <QObject>
// #include <QSerialPort>
// #include <QThread>

// #include "com.h"

// using namespace MCOM;

// namespace PORT_THREAD {
// class ListenPortThread : public QThread  {
//     Q_OBJECT
//    private:
//     const QSerialPort* serialPort;

//    public:
//     ListenPortThread(const QSerialPort *port) { serialPort = port; };

//     void run();
//    signals:
//     void GetData(const QString &data);
//    private slots:
//     void errorHandlerInThread(QSerialPort::SerialPortError error);

// };

// }  // namespace PORT_THREAD

// #endif  // LISTENPORTTHREAD_H

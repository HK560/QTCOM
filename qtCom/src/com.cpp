#include "include/com.h"
using namespace MCOM;

COM::COM() {
    serialPort = new QSerialPort();
    connect(serialPort, &QSerialPort::errorOccurred, this, &COM::errorHandle);
    connect(serialPort,&QSerialPort::readyRead,this,&COM::SendDataToMainwindow);
}

COM::~COM() { delete serialPort; }
/**
 * @brief 用于开启端口，需要先使用SettingPort()设置好端口信息
 * @description:
 * @return {*}返回bool是否开启成功
 */
bool COM::OpenPort() {
    if (serialPort != NULL && !serialPort->isOpen()) {
        if (serialPort->open(QIODevice::ReadWrite)) {
            qDebug() << "open port:" << serialPort->portName()
                     << serialPort->isOpen();
            return true;
        };
    }
    QMessageBox::warning(NULL, tr("信息"), tr("打开端口失败"), QMessageBox::Ok);

    return false;
}

/**
 * @brief 用于设置要开启的端口的名字，波特率，数据位等等信息
 * @description:
 * @param {SerialPortSetting&} settingStruct 传入端口设置信息结构体
 * @return {*}返回bool是否成功
 */
bool COM::SettingPort(const SerialPortSetting& settingStruct) {
    if (serialPort != NULL) {
        serialPort->setPortName(settingStruct.portName);
        serialPort->setDataBits(settingStruct.dataBits);
        serialPort->setBaudRate(settingStruct.baudRate);
        serialPort->setFlowControl(settingStruct.flowControl);
        serialPort->setParity(settingStruct.parity);
        serialPort->setStopBits(settingStruct.stopBits);
        qDebug() << "SettingPort: " << serialPort->portName()
                 << serialPort->baudRate();
        portReady = true;
        return true;
    }
    QMessageBox::warning(NULL, tr("错误"), tr("端口未实例"), QMessageBox::Ok);
    return false;
};

bool COM::ClosePort() {
    if (serialPort != NULL) {
        if (portReady) {
            serialPort->close();
            portReady = false;
            qDebug()<<"串口关闭成功";
            return true;
        } else {
            QMessageBox::warning(NULL, tr("错误"), tr("端口未开启"),
                                 QMessageBox::Ok);
            return false;
        }
    }
    QMessageBox::warning(NULL, tr("错误"), tr("端口未实例"), QMessageBox::Ok);
    return false;
}

bool COM::SendMessageToPort(const QString& data) {
    if (portReady) {
        QByteArray dataBuffer = data.toLocal8Bit();
        serialPort->write(dataBuffer);
        if (!serialPort->waitForBytesWritten()) {
            errorHandle(QSerialPort::WriteError);
        }
        return true;
    }
    QMessageBox::warning(NULL, tr("错误"), tr("端口还没有打开或配置"),
                         QMessageBox::Ok);
    return false;
}

void COM::errorHandle(QSerialPort::SerialPortError error) {
    QString errorStr;
    errorStr.clear();
    switch (error) {
        case QSerialPort::NoError:
            break;
        case QSerialPort::OpenError:
            errorStr = tr("错误端口已打开");
            break;
        case QSerialPort::WriteError:
            errorStr = tr("向串口写入数据出错");
            break;
        case QSerialPort::ReadError:
            errorStr = tr("向串口读出数据出错");
            break;
        default:
            errorStr = tr("未知错误");
    }
    if (!errorStr.isEmpty()) {
        portReady = false;
        QMessageBox::warning(NULL, tr("错误"), errorStr);
    }
}


void COM::SendDataToMainwindow(){
    QByteArray dataBuffer = serialPort->readAll(); 
    emit ReceiveData(dataBuffer);
    return;
}


volatile bool COM::portReady = false;

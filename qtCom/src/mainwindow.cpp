#include "mainwindow.h"

#include "com.h"
#include "ui_mainwindow.h"

volatile bool MainWindow::usingPort = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    portInfo = new MCOMINFO::comPortInfo();
    port = nullptr;
    logText = new QByteArray();
    refreshPortInfoToUI();
}

MainWindow::~MainWindow() {
    delete ui;
    delete logText;
    delete portInfo;
}

void MainWindow::on_refreshBtn_clicked() { refreshPortInfoToUI(); }

void MainWindow::refreshPortInfoToUI() {
    ui->comPortSelect->clear();
    ui->comPortSelect->addItems(MCOMINFO::comPortInfo::GetComPortInfo());

    ui->bandSelect->clear();
    ui->bandSelect->addItems(MCOMINFO::comPortInfo::GetCombaudInfo());
}

void MainWindow::on_sendBtn_clicked() {
    if (usingPort == false) {
        QMessageBox::warning(this, tr("警告"),
                             tr("还没有开启串口或初始化串口"));
        return;
    } else {
        QString dataToSend = ui->lineEdit->text();
        qDebug() << "going to send:" << dataToSend;
        if (port != NULL && port->PortIsReady()) {
            if (!port->SendMessageToPort(dataToSend)) {
                QMessageBox::warning(this, tr("错误"), tr("发送错误"));
                return;
            }
            ui->logEdit->append(dataToSend + "\n");
        }
        return;
    }
}

void MainWindow::on_openPortBtn_clicked() {
    PortInit();

    MCOM::SerialPortSetting portSettingInit;
    portSettingInit.portName = ui->comPortSelect->currentText();
    portSettingInit.baudRate =
        MCOMINFO::comPortInfo::baudInfo.find(ui->bandSelect->currentText())
            .value();
    portSettingInit.dataBits = QSerialPort::Data8;
    portSettingInit.flowControl = QSerialPort::NoFlowControl;
    portSettingInit.parity = QSerialPort::NoParity;
    portSettingInit.stopBits = QSerialPort::OneStop;

    if (port->SettingPort(portSettingInit)) {
        if (port->OpenPort()) {
            QMessageBox::information(this, tr("信息"), tr("打开串口成功"),
                                     QMessageBox::Ok);
            usingPort = true;
        }
        // ui->openPortBtn->setDisabled(true);  //禁用按钮
    } else
        QMessageBox::warning(this, tr("错误"), tr("打开串口失败"),
                             QMessageBox::Ok);
}

/**
 * @brief 为当前COM 实例化，如果已经存在对象则delete再重新实例化
 * @description:
 * @return {*}
 */
bool MainWindow::PortInit() {
    if (port != NULL) {
        delete port;
        qDebug() << "delete port";
    } else {
        qDebug() << "port is NULL";
    }
    // else {
    //     qDebug() << "port is null when try to open port ";
    //     QMessageBox::warning(this, tr("错误"), tr("还未设置串口参数初始化"));
    //     return;

    port = new MCOM::COM();
    if (port != NULL) {
        connect(port, &MCOM::COM::ReceiveData, this,
                &MainWindow::GetDataFromPort);
        return true;
    } else
        return false;
}

void MainWindow::GetDataFromPort(const QByteArray &data) {
    qDebug() << "GetDataFromPort" << data.toHex();
    // ui->logEdit->append(data);
    logText->append(data);
    qDebug() << "nowlogText" << *logText;
    // logText->append("\n");
    on_hexCheckBox_stateChanged(ui->hexCheckBox->checkState());
}
void MainWindow::on_hexCheckBox_stateChanged(int arg1) {
    if (arg1 == Qt::Unchecked) {
        QString text = *logText;
        // QString dataString = dataBuffer;
         QTextCodec *tc =QTextCodec::codecForName("GBK");
        text = tc->toUnicode(*logText);
        ui->logEdit->setText(text);
        // qDebug() << "on_hexCheckBox_stateChanged" << text;

    } else if (arg1 == Qt::Checked) {
        QString text;
        // text = text.replace(" ","");
        QByteArray textHex = *logText;
        // qDebug() << "textHex:" << textHex.toHex();
        text = textHex.toHex().toUpper();
        // text = text.replace("20", "");

        for (int i = 2; i < text.size(); i += 2 + 1) {
            text.insert(i, " ");
        }
    //    text = text.replace("0A", "\n");

        // text.append("\n");
        ui->logEdit->clear();
        ui->logEdit->setText(text);
    }
}

void MainWindow::on_logEdit_textChanged() {
    // *logText =
}

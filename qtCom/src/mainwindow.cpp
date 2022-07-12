#include "include/mainwindow.h"

#include "include/com.h"
#include "ui_mainwindow.h"

volatile bool MainWindow::usingPort = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    portInfo = new MCOMINFO::comPortInfo();
    port = nullptr;
    logText = new QByteArray();
    sendText = new QString();
    QRegExp regExpHEX = QRegExp("[A-Fa-f0-9\\s]*");

    validatorLineEditHEX = new QRegExpValidator(regExpHEX);

    refreshPortInfoToUI();
}

MainWindow::~MainWindow() {
    delete ui;
    delete logText;
    delete portInfo;
}

void MainWindow::on_refreshBtn_clicked() { refreshPortInfoToUI(); }

/**
 * @brief 更新UI信息，更新可用的串口波特率等等
 * @description:
 * @return {*}
 */
void MainWindow::refreshPortInfoToUI() {
    ui->comPortSelect->clear();
    ui->comPortSelect->addItems(MCOMINFO::comPortInfo::GetComPortInfo());

    ui->bandSelect->clear();
    ui->bandSelect->addItems(MCOMINFO::comPortInfo::GetCombaudInfo());

    ui->flowControlSelect->clear();
    ui->flowControlSelect->addItems(MCOMINFO::comPortInfo::flowControlStrList);

    ui->dataBitsSelect->clear();
    ui->dataBitsSelect->addItems(MCOMINFO::comPortInfo::dataBitsStrList);

    ui->paritySelect->clear();
    ui->paritySelect->addItems(MCOMINFO::comPortInfo::parityStrList);

    ui->stopBitsSelect->clear();
    ui->stopBitsSelect->addItems(MCOMINFO::comPortInfo::stopBitsStrList);
}

/**
 * @brief 向串口发送信息
 * @description:
 * @return {*}
 */
void MainWindow::on_sendBtn_clicked() {
    if (usingPort == false) {
        QMessageBox::warning(this, tr("警告"),
                             tr("还没有开启串口或初始化串口"));
        return;
    } else {
        // QString dataToSend = ui->lineEdit->text();
        // qDebug() << "going to send:" << dataToSend;
        // if (port != NULL && port->PortIsReady()) {
        //     if (!port->SendMessageToPort(dataToSend)) {
        //         QMessageBox::warning(this, tr("错误"), tr("发送错误"));
        //         return;
        //     }
        //     // ui->logEdit->append(dataToSend + "\n");
        // }
        switch (ui->hexSendCheckBox->checkState()) {
            case Qt::Checked: {
                QByteArray data;
                data = QByteArray::fromHex(
                    ui->lineEdit->text().simplified().toUtf8());
                ui->lineEdit->setText(data.toHex().toUpper());
                qDebug() << "going to send:" << data.toHex();
                if (port != NULL && port->PortIsReady()) {
                    if (!port->SendMessageToPort(data)) {
                        QMessageBox::warning(this, tr("错误"), tr("发送错误"));
                        return;
                    }
                    break;
                }
            }
            case Qt::Unchecked: {
                QByteArray data = ui->lineEdit->text().toLocal8Bit();
                qDebug() << "going to send:" << data;
                if (port != NULL && port->PortIsReady()) {
                    if (!port->SendMessageToPort(data)) {
                        QMessageBox::warning(this, tr("错误"), tr("发送错误"));
                        return;
                    }
                    break;
                }
                break;
            }
            default:
                QMessageBox::warning(this, tr("错误"), tr("未成功发送"));
                break;
        }

        return;
    }
}

/**
 * @brief 打开串口或关闭串口按钮槽函数，用于初始化串口并开启，或者关闭串口
 * @description:
 * @return {*}
 */
void MainWindow::on_openPortBtn_clicked() {
    if (!usingPort) {
        PortInit();

        MCOM::SerialPortSetting portSettingInit;
        portSettingInit.portName = ui->comPortSelect->currentText();
        portSettingInit.baudRate =
            MCOMINFO::comPortInfo::baudInfo.find(ui->bandSelect->currentText())
                .value();
        portSettingInit.dataBits = MCOMINFO::comPortInfo::dataBitsInfo
                                       .find(ui->dataBitsSelect->currentText())
                                       .value();
        portSettingInit.flowControl =
            MCOMINFO::comPortInfo::flowControlInfo
                .find(ui->flowControlSelect->currentText())
                .value();
        portSettingInit.parity = MCOMINFO::comPortInfo::parityInfo
                                     .find(ui->paritySelect->currentText())
                                     .value();
        portSettingInit.stopBits = MCOMINFO::comPortInfo::stopBitsInfo
                                       .find(ui->stopBitsSelect->currentText())
                                       .value();

        if (port->SettingPort(portSettingInit)) {
            if (port->OpenPort()) {
                usingPort = true;
                ui->openPortBtn->setText(tr("关闭串口"));
                ui->bandSelect->setDisabled(true);
                ui->comPortSelect->setDisabled(true);
                ui->stopBitsSelect->setDisabled(true);
                ui->dataBitsSelect->setDisabled(true);
                ui->flowControlSelect->setDisabled(true);
                ui->paritySelect->setDisabled(true);

            } else {
                QMessageBox::warning(this, tr("错误"), tr("打开串口失败"),
                                     QMessageBox::Ok);
            }
        } else
            QMessageBox::warning(this, tr("错误"), tr("初始化串口信息失败"),
                                 QMessageBox::Ok);
    } else {
        if (!port->ClosePort()) {
            QMessageBox::warning(this, tr("错误"), tr("关闭串口失败"));
            // to do : 是否销毁串口对象，重启，检测状态
            return;
        } else {
            usingPort = false;
            ui->openPortBtn->setText(tr("打开串口"));
            ui->bandSelect->setEnabled(true);
            ui->comPortSelect->setEnabled(true);
            ui->stopBitsSelect->setEnabled(true);
            ui->dataBitsSelect->setEnabled(true);
            ui->flowControlSelect->setEnabled(true);
            ui->paritySelect->setEnabled(true);
            return;
        }
    }
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

/**
 * @brief 槽函数 从开启的串口处接受数据并写入到静态变量logText
 * @description:
 * @param {QByteArray} &data  串口接受到的数据
 * @return {*}
 */
void MainWindow::GetDataFromPort(const QByteArray &data) {
    qDebug() << "GetDataFromPort" << data.toHex();
    // ui->logEdit->append(data);
    logText->append(data);
    qDebug() << "nowlogText" << *logText;
    // logText->append("\n");
    on_hexCheckBox_stateChanged(ui->hexCheckBox->checkState());
}

/**
 * @brief 根据是否勾选了十六进制显示来切换串口数据信息显示方式
 * @description:
 * @param {int} arg1  复选框状态
 * @return {*}
 */
void MainWindow::on_hexCheckBox_stateChanged(int arg1) {
    if (arg1 == Qt::Unchecked) {
        QString text = *logText;
        // QString dataString = dataBuffer;
        QTextCodec *tc = QTextCodec::codecForName("GBK");
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

void MainWindow::on_clearBtn_clicked() {
    logText->clear();
    ui->logEdit->clear();
}

void MainWindow::on_hexSendCheckBox_stateChanged(int arg1) {
    switch (arg1) {
        case Qt::Checked: {
            // QString text = ;
            qDebug() << "on_hexSendCheckBox_stateChanged" << arg1;
            QString text = *sendText;
            qDebug() << "lineEdit text：" << text;

            ui->lineEdit->setValidator(validatorLineEditHEX);
            ui->lineEdit->clear();

            QByteArray data = text.toLocal8Bit();
            ui->lineEdit->setText(data.toHex().toUpper());
            // ui->lineEdit->
            break;
        }
        case Qt::Unchecked: {
            qDebug() << "on_hexSendCheckBox_stateChanged" << arg1;

            // QString text;
            // QByteArray data ;
            // data = arg1.toUtf8();
            // QTextCodec *tc = QTextCodec::codecForName("GBK");
            // text = tc->toUnicode(data);
            QString text = *sendText;
            qDebug() << "lineEdit text：" << text;

            ui->lineEdit->setValidator(0);
            ui->lineEdit->clear();

            // text.toLocal8Bit();
            ui->lineEdit->setText(text);
            break;
        }
        default:
            return;
    }
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1) {
    switch (ui->hexSendCheckBox->checkState()) {
        case Qt::Checked: {
            // QString text = arg1;
            // qDebug() << "lineEdit text："<<text;
            // text.toLocal8Bit();
            // ui->lineEdit->setText(text);
            // // QRegExp regExp = QRegExp("[A-Za-z0-9]+");

            // // QValidator *validatorName = new QRegExpValidator(regExp);
            // // ui->lineEdit->setValidator(validatorName);
            // // ui->lineEdit->
            QString text;
            QByteArray data;

            data = QByteArray::fromHex(arg1.simplified().toUtf8());
            qDebug() << data.toHex();

            QTextCodec *tc = QTextCodec::codecForName("GBK");
            text = tc->toUnicode(data);
            *sendText = text;
            qDebug() << "now send text::" << *sendText;
            // text = arg1

            break;
        }
        case Qt::Unchecked: {
            //             QString text = arg1;
            // qDebug() << "lineEdit text："<<text;
            *sendText = arg1;
            break;
        }
        default:
            return;
    }
}

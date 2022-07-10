#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "comportinfo.h"
#include "com.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void refreshPortInfoToUI();
    ~MainWindow();

private slots:
    void on_refreshBtn_clicked();

    void on_sendBtn_clicked();

    void on_openPortBtn_clicked();

    void GetDataFromPort(const QByteArray &data);

    void on_hexCheckBox_stateChanged(int arg1);



    void on_logEdit_textChanged();

private:
    Ui::MainWindow *ui;
    MCOMINFO::comPortInfo *portInfo;
    MCOM::COM* port;

    bool PortInit();
    volatile static bool usingPort; // 标记是否正在使用串口

    QByteArray* logText;

};
#endif // MAINWINDOW_H
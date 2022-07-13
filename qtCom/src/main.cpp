#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QTranslator>

#include "include/mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    if (QLocale::system().name() != "zh_CN") {
        qDebug() << "nochinese language";
        QTranslator *qtTranslatorBase = new QTranslator;
        if (qtTranslatorBase->load("../language_en.qm")) {
            a.installTranslator(qtTranslatorBase);
            qDebug() << "loaded ";
        } else {
            qDebug() << "unloaded ";
        }
    }
QFile qss("../style.qss");
qss.open(QFile::ReadOnly);
a.setStyleSheet(qss.readAll());
qss.close();
    MainWindow w;
    w.show();
    return a.exec();
}

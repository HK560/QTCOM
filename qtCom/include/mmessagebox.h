#ifndef MMESSAGEBOX_H
#define MMESSAGEBOX_H

#include <QMessageBox>
#include <QVBoxLayout>
#include <QFrame>
#include <QPainter>
#include <QBitmap>

class MMessagebox : public QMessageBox {
   public:
    MMessagebox();
    static void warning(QWidget *parent, const QString &title, const QString &text);
    protected:
    // void paintEvent(QPaintEvent *event) override;
    
};

#endif  // MMESSAGEBOX_H

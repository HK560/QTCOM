#include "mmessagebox.h"

MMessagebox::MMessagebox() {}

void MMessagebox::warning(QWidget *parent, const QString &title,
                          const QString &text) {
    QMessageBox messagebox;
    messagebox.setWindowFlags(Qt::FramelessWindowHint | 
               Qt::WindowMinimizeButtonHint |
               Qt::WindowStaysOnTopHint);
            //    messagebox.setAttribute(Qt::WA_TranslucentBackground);

    messagebox.setText(text);
    messagebox.setWindowTitle(title);
    messagebox.setIcon(QMessageBox::Warning);
    messagebox.setStandardButtons(QMessageBox::Close);
    messagebox.show();
    const QRect rect(QPoint(0,0), messagebox.geometry().size());
    QBitmap b(rect.size());
    b.fill(QColor(Qt::color0));
    QPainter painter(&b);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::color1);
    // this radius should match the CSS radius
    painter.drawRoundedRect(rect, 15, 15);
    painter.end();
    messagebox.setMask(b);
    messagebox.exec();
}


// void MMessagebox::paintEvent(QPaintEvent *event)
// {
// 	QPainter painter(this);
// 	painter.setRenderHint(QPainter::Antialiasing);	// 反锯齿;
// 	painter.setBrush(QBrush(Qt::red));
// 	painter.setPen(Qt::transparent);
// 	QRect rect = this->rect();
// 	rect.setWidth(rect.width() - 1);
// 	rect.setHeight(rect.height() - 1);
// 	painter.drawRoundedRect(rect, 15, 15);
// 	// //也可用QPainterPath 绘制代替 painter.drawRoundedRect(rect, 15, 15);
// 	// {
// 	// 	QPainterPath painterPath;
// 	// 	painterPath.addRoundedRect(rect, 15, 15);
// 	// 	p.drawPath(painterPath);
// 	// }
// 	QWidget::paintEvent(event);
// }
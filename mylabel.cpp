#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
     this->setMouseTracking(true);
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    int pixel[2];
    QString str = QString("pressed, X = %1,Y = %2").arg(ev->x()).arg(ev->y());
    pixel[0] = ev->x();
    pixel[1] = ev->y();
    qDebug() <<str ;
    emit sendPixel(pixel);
}

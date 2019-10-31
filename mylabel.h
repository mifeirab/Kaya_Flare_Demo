#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *ev);
signals:
    void sendPixel(int*);
public slots:

private:

};

#endif // MYLABEL_H

#ifndef SEATCOLOR_H
#define SEATCOLOR_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

class SeatColor : public QGraphicsObject
{
    Q_OBJECT

public:
    enum State{Red=Qt::red,Green=Qt::green};
    SeatColor(QGraphicsObject *parent=0);

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

public slots:
    void setRed();
    void setGreen();

private:
    State mState=State::Green;    
};

#endif // SEATCOLOR_H

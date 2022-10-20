#include "SeatColor.h"

SeatColor::SeatColor(QGraphicsObject *parent): QGraphicsObject(parent)
{

}

QRectF SeatColor::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void SeatColor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor(Qt::GlobalColor((mState == Red)? Red : Green)));
    painter->drawRect(QRect(12,5,25,25));
}

void SeatColor::setRed()
{
    mState = Red;
    update();
}

void SeatColor::setGreen()
{
    mState = Green;
    update();
}


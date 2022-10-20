#include "SeatWidget.h"
#include "ui_SeatWidget.h"
#include "SeatColor.h"

SeatWidget::SeatWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SeatWidget)
{
    ui->setupUi(this);
    mScene = new QGraphicsScene(0,0,500,500,this);
    ui->graphicsView->setScene(mScene);

    QList<QGraphicsItem *> items = mScene->items();
    for(QGraphicsItem* i : items)
    {
        qDebug() << i->data(0x100).toString();
    }

    SeatColor* seat = new SeatColor();
    seat->setGreen();
    seat->setFlag(QGraphicsItem::ItemIsMovable,false);
    //deplacer le siege moveby
    mScene->addItem(seat);
}

SeatWidget::~SeatWidget()
{
}


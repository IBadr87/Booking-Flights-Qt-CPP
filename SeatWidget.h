#ifndef SEATWIDGET_H
#define SEATWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class SeatWidget; }
QT_END_NAMESPACE

class SeatWidget : public QWidget
{
    Q_OBJECT

public:
    SeatWidget(QWidget *parent);
    ~SeatWidget();

private:
    Ui::SeatWidget *ui;
    QGraphicsScene* mScene;
};
#endif // SEATWIDGET_H

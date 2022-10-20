#ifndef POSTDATA_H
#define POSTDATA_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QJsonObject>
#include <time.h>

class PostData: public QObject
{
    Q_OBJECT
public:
    PostData();
    void postCustomer(QJsonObject &customer);
    void postReservation(QJsonObject &reservation);

};

#endif // POSTDATA_H

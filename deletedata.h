#ifndef DELETEDATA_H
#define DELETEDATA_H

#include <QObject>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QJsonObject>

class DeleteData: public QObject
{
    Q_OBJECT
public:
    DeleteData();
    QJsonObject deleteCustomer(int& customer_id);
    QJsonObject deleteReservation(int& reservation_id);
};

#endif // DELETEDATA_H

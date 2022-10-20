#ifndef UPDATEDATA_H
#define UPDATEDATA_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QJsonObject>

class UpdateData: QObject
{
    Q_OBJECT
public:
    UpdateData();
    void updateCustomer(QJsonObject &customer);
    void updateReservation(QJsonObject &reservation);


};

#endif // UPDATEDATA_H

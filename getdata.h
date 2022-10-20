#ifndef GETDATA_H
#define GETDATA_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QJsonObject>

class GetData: public QObject
{
    Q_OBJECT
public:
    GetData();
    QJsonObject getCompanyAll();
    QJsonObject getCompanyId(int &company_id);
    QJsonObject getCustomerAll();
    QJsonObject getCustomerId(int &customer_id);
    QJsonObject getReservationFlightId(int &flight_id); // TO DO
    QJsonObject getReservationCustomerId(int &customer_id);  // TO DO
    QJsonObject getPlaneAll();
    QJsonObject getPlaneId(int &plane_id);
    QJsonObject getFlightAll();
    QJsonObject getFlightId(int &flight_id);



};

#endif // GETDATA_H

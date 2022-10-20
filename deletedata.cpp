#include "deletedata.h"

DeleteData::DeleteData()
{

}

QJsonObject DeleteData::deleteCustomer(int &customer_id)
{
    QString request;
    request = QString("delete from Customer where customer_id = %1").arg(customer_id);
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(db);
    if (db.open() == true)
    {
        query.prepare(request);
        query.exec();
        return QJsonObject{{{"result", 200}}};
    }
    else
    {
        qDebug() << "db not open";
    }
    qDebug() << query.lastQuery();
    return  QJsonObject{{{"result", 404}}};

}

QJsonObject DeleteData::deleteReservation(int &reservation_id)
{
    QString request;
    request = QString("delete from Reservation where reservation_id = %1").arg(reservation_id);
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(db);
    if (db.open() == true)
    {
        query.prepare(request);
        query.exec();
        return QJsonObject{{{"result", 200},{"reservation_id", reservation_id}}};
    }
    else
    {
        qDebug() << "db not open";
    }
    qDebug() << query.lastQuery();
    return  QJsonObject{{{"result", 404}}};
}



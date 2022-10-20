#include "postdata.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <string>
#include <ctime>

using namespace std;

PostData::PostData()
{

}

void PostData::postCustomer(QJsonObject &customer)
{
    QString request;
    QString passport_id, last_name, first_name, email, telephone;
    passport_id = customer["passport_id"].toString();
    last_name = customer["lastName"].toString();
    first_name = customer["firstName"].toString();
    email = customer["email"].toString();
    telephone = customer["telephone"].toString();
    request = "insert into Customer (passport_id, lastName, firstName, email, telephone) values (?, ?, ?, ?, ?)";
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(db);
    if(db.open() == true)
    {
        query.prepare(request);
        query.addBindValue(passport_id);
        query.addBindValue(last_name);
        query.addBindValue(first_name);
        query.addBindValue(email);
        query.addBindValue(telephone);
        query.exec();
    }
    else
    {
        qDebug() << "The database is not open";
    }

    qDebug() << query.lastQuery();
}


void PostData::postReservation(QJsonObject &reservation)
{
    QString request;
    QString customer_id, flight_id, line_seat, uuid;
    QString first_name, last_name, reserv_time, column_seat, reserv_cancel;
    customer_id = reservation["customer_id"].toString();
    flight_id = reservation["flight_id"].toString();
    first_name = reservation["firstNamePassenger"].toString();
    last_name = reservation["lastNamePassenger"].toString();
    reserv_time = reservation["reservationTime"].toString();
    reserv_cancel = reservation["reservationCanceled"].toString();
    line_seat = reservation["seatRowNumber"].toString();
    column_seat = reservation["seatColumnNumber"].toString();
    uuid = reservation["uuid"].toString();
    request = "insert into Reservation (customer_id, flight_id, firstNamePassenger, lastNamePassenger,\
               reservationTime, reservationCanceled, seatRowNumber, seatColumnNumber, uuid) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(db);
    if (db.open() == true)
    {
        query.prepare(request);
        query.addBindValue(customer_id.toInt());
        query.addBindValue(flight_id.toInt());
        query.addBindValue(first_name);
        query.addBindValue(last_name);
        query.addBindValue(reserv_cancel);
        query.addBindValue(reserv_cancel);
        query.addBindValue(line_seat.toInt());
        query.addBindValue(column_seat);
        query.addBindValue(uuid);
        query.exec();
    }
    else
        qDebug() << query.lastQuery();

}



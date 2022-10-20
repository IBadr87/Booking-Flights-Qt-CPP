#include "updatedata.h"
#include "postdata.h"

UpdateData::UpdateData()
{

}

void UpdateData::updateCustomer(QJsonObject &customer)
{
    QString request;
    int customer_id;
    QString passport_id, last_name, first_name, email, telephone;
    customer_id = customer["customer_id"].toInt();
    passport_id = customer["passport_id"].toString();
    last_name = customer["lastName"].toString();
    first_name = customer["firstName"].toString();
    email = customer["email"].toString();
    telephone = customer["telephone"].toString();
    request= QString("UPDATE Customer SET passport_id = '%1', lastName = '%2', firstName = '%3',\
                     email = '%4', telephone = '%5' WHERE customer_id = %6").arg(passport_id).arg(last_name)\
                     .arg(first_name).arg(email).arg(telephone).arg(customer_id);
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(db);
    if (db.open() == true)
    {
        query.prepare(request);
        query.exec();
    }
    else
    {
        qDebug() << "db not open";
    }
    qDebug() << query.lastQuery();
}

void UpdateData::updateReservation(QJsonObject &reservation)
{
    QString request;
    int reservation_id, flight_id, customer_id, row_seat;
    QString uuid, first_name, last_name, reserv_time, column_seat, reserv_cancel;
    reservation_id = reservation["reservation_id"].toInt();
    flight_id = reservation["flight_id"].toInt();
    customer_id = reservation["customer_id"].toInt();
    uuid = reservation["uuid"].toString();
    reserv_time = reservation["reservationTime"].toString();
    reserv_cancel = reservation["reservationCanceled"].toString();
    column_seat = reservation["seatColumnNumber"].toString();
    row_seat = reservation["seatRowNumber"].toInt();

    request= QString("UPDATE Reservation SET uuid = '%1', reservationTime = '%2', reservationCanceled = '%3',\
                     seatColumnNumber = '%4', seatRowNumber = %5, flight_id = %6, customer_id = %7 WHERE reservation_id = %8")\
            .arg(uuid).arg(reserv_time).arg(reserv_cancel).arg(column_seat).arg(row_seat).arg(flight_id).arg(customer_id).arg(reservation_id);
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(db);
    if (db.open() == true)
    {
        query.prepare(request);
        query.exec();
    }
    else
    {
        qDebug() << "db not open";
    }
    qDebug() << query.lastQuery();



}























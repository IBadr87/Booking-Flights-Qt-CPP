#include "getdata.h"
#include <QJsonArray>
#include <QJsonDocument>

GetData::GetData()
{

}

QJsonObject GetData::getCompanyAll()
{

    QJsonArray companies_arr;
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query("select * from Company", db);
    while(query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QJsonObject company;
        company["company_id"] = id;
        company["companyName"] = name;
        companies_arr.append(company);
    }

    QJsonObject companies_json;
    companies_json["allCompany"] = companies_arr;


    return companies_json;
}

QJsonObject GetData::getCompanyId(int &company_id)
{
    QString request;
    request = "select * from Company where company_id=";
    request += QString::number(company_id);
    QJsonObject company;
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(request, db);
    while(query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        company["company_id"] = id;
        company["companyName"] = name;
    }

    return company;
}

QJsonObject GetData::getCustomerAll()
{
    QJsonArray customers_arr;
    QString request;
    request = "select * from Customer";
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(request, db);
    while(query.next())
    {
        int customer_id = query.value(0).toInt();
        QString passport_id = query.value(1).toString();
        QString last_name = query.value(2).toString();
        QString first_name = query.value(3).toString();
        QString email = query.value(4).toString();
        QString telephone = query.value(5).toString();
        QJsonObject customer;
        customer["customer_id"] = customer_id;
        customer["passport_id"] = passport_id;
        customer["lastName"] = last_name;
        customer["firstName"] = first_name;
        customer["email"] = email;
        customer["telephone"] = telephone;
        customers_arr.append(customer);
    }

    QJsonObject customers_json;
    customers_json["allCustomers"] = customers_arr;


    return customers_json;
}

QJsonObject GetData::getCustomerId(int &customer_id)
{
    QString request;
    request = "select * from Customer where customer_id=";
    request += QString::number(customer_id);
    QJsonObject customer;
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(request, db);
    while(query.next())
    {
        int customer_id = query.value(0).toInt();
        QString passport_id = query.value(1).toString();
        QString last_name = query.value(2).toString();
        QString first_name = query.value(3).toString();
        QString email = query.value(4).toString();
        QString telephone = query.value(5).toString();
        customer["customer_id"] = customer_id;
        customer["passport_id"] = passport_id;
        customer["lastName"] = last_name;
        customer["firstName"] = first_name;
        customer["email"] = email;
        customer["telephone"] = telephone;
    }

    return customer;
}

QJsonObject GetData::getReservationFlightId(int &flight_id)
{
    QJsonArray data;
    QString request1, request2;
    QJsonObject flight;
    request1 = "select * from Reservation join Flights on Reservation.flight_id\
               = Flights.flight_id where Reservation.flight_id = ";
    request1 += QString::number(flight_id);
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(request1, db);
    while(query.next())
    {
        QJsonObject customer, update_data;
        QJsonArray reservations;
        int customer_id = query.value(3).toInt();
        request2 = QString("select * from Reservation join Flights on Reservation.flight_id=\
                           Flights.flight_id where Reservation.flight_id = %1 and \
                           Reservation.customer_id = %2").arg(flight_id).arg(customer_id);
        QString passport_id = query.value(1).toString();
        QString last_name = query.value(2).toString();
        QString first_name = query.value(3).toString();
        QString email = query.value(4).toString();
        QString telephone = query.value(5).toString();
        customer["customer_id"] = customer_id;
        customer["passport_id"] = passport_id;
        customer["lastName"] = last_name;
        customer["firstName"] = first_name;
        customer["email"] = email;
        customer["telephone"] = telephone;
        update_data["customer"] = customer;
        QSqlQuery query(request2, db);
        while(query.next())
        {
            QJsonObject reservation;
            reservation["uuid"] = query.value(2).toString();
            reservation["firstNamePassenger"] = query.value(4).toString();
            reservation["lastNamePassenger"] = query.value(5).toString();
            reservation["reservationTime"] = query.value(6).toString();
            reservation["reservationCanceled"] = query.value(7).toString();
            reservation["seatRowNumber"] = query.value(8).toInt();
            reservation["seatColumnNumber"] = query.value(9).toString();
            reservations.append(reservation);
        }
        update_data["reservations"] = reservations;
        data.append(update_data);
    }
    QJsonObject result;
    result["flights"] = getFlightId(flight_id);
    result["allReservation"] = data;

    return result;
}


QJsonObject GetData::getReservationCustomerId(int &customer_id)
{
    QJsonArray data;
    QString request1, request2;
    request1 = "select * from Reservation join Flights on Reservation.flight_id = \
                Flights.flight_id where Reservation.customer_id = ";
    request1 += QString::number(customer_id);
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(request1, db);
    while(query.next())
    {
        QJsonObject flight, update_data;
        QJsonObject reservation;
        QJsonArray reservations;
        int flight_id = query.value(1).toInt();
        flight = getFlightId(flight_id);
        request2 =QString( "select * from Reservation join Flights on Reservation.flight_id = \
                            Flights.flight_id where Reservation.customer_id = %1 and reservation.flight_id\
                            = %2").arg(customer_id).arg(flight_id);

        QSqlQuery query(request2, db);
        while(query.next())
        {
            reservation["reservation_id"] = query.value(0).toInt();
            reservation["uuid"] = query.value(2).toString();
            reservation["firstNamePassenger"] = query.value(4).toString();
            reservation["lastNamePassenger"] = query.value(5).toString();
            reservation["reservationTime"] = query.value(6).toString();
            reservation["reservationCanceled"] = query.value(7).toString();
            reservation["seatRowNumber"] = query.value(8).toInt();
            reservation["seatColumnNumber"] = query.value(9).toString();
            reservations.append(reservation);
        }

        update_data["flights"] = flight;
        update_data["reservations"] = reservations;
        data.append(update_data);
    }
    QJsonObject result;
    result["data"] = data;

    return result;
}


QJsonObject GetData::getPlaneAll()
{
    QJsonArray planes_arr;
    QString request;
    request = "select * from Plane";
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(request, db);
    while(query.next())
    {
        int plane_id = query.value(0).toInt();
        QString model = query.value(1).toString();
        QString seat_row = query.value(2).toString();
        QString seat_col = query.value(3).toString();
        QString aquisition_date = query.value(4).toString();
        QJsonObject plane;
        plane["plane_id"] = plane_id;
        plane["planeModel"] = model;
        plane["numberOfSeatRow"] = seat_row;
        plane["numberOfSeatColumn"] = seat_col;
        plane["acquisitionDate"] = aquisition_date;
        planes_arr.append(plane);
    }

    QJsonObject planes_json;
    planes_json["allPlanes"] = planes_arr;

    return planes_json;
}

QJsonObject GetData::getPlaneId(int &plane_id)
{
    QString request;
    request = "select * from Customer where customer_id=";
    request += QString::number(plane_id);
    QJsonObject plane;
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(request, db);
    while(query.next())
    {
        int plane_id = query.value(0).toInt();
        QString model = query.value(1).toString();
        QString seat_row = query.value(2).toString();
        QString seat_col = query.value(3).toString();
        QString aquisition_date = query.value(4).toString();
        plane["plane_id"] = plane_id;
        plane["planeModel"] = model;
        plane["numberOfSeatRow"] = seat_row;
        plane["numberOfSeatColumn"] = seat_col;
        plane["acquisitionDate"] = aquisition_date;
    }

    return plane;
}

QJsonObject GetData::getFlightAll()
{
    QJsonArray flights_arr;
    QString request;
    request = "select * from Flights inner join Plane on Flights.flight_id=Plane.plane_id";
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(request, db);

    while(query.next())
    {
        int flight_id = query.value(0).toInt();
        int company_id = query.value(2).toInt();
        QString depart_city = query.value(3).toString();
        QString arrival_city = query.value(4).toString();
        QString depart_date = query.value(5).toString();
        QString depart_time = query.value(6).toString();
        QString arrival_date = query.value(7).toString();
        QString arrival_time = query.value(8).toString();
        int plane_id = query.value(9).toInt();
        QString model = query.value(10).toString();
        QString seat_row = query.value(11).toString();
        QString seat_column = query.value(12).toString();
        QString acquisition_date = query.value(13).toString();
        QJsonObject flight;
        flight["flight_id"] = flight_id;
        flight["company_id"] = company_id;
        flight["plane_id"] = plane_id;
        flight["planeModel"] = model;
        flight["numberOfSeatRow"] = seat_row;
        flight["numberOfSeatColumn"] = seat_column;
        flight["acquisitionDate"] = acquisition_date;
        flight["departureCity"] = depart_city;
        flight["arrivalCity"] = arrival_city;
        flight["departureDate"] = depart_date;
        flight["departureTime"] = depart_time;
        flight["arrivalDate"] = arrival_date;
        flight["arrivalTime"] = arrival_time;
        flights_arr.append(flight);
    }

    QJsonObject flights_json;
    flights_json["allFlights"] = flights_arr;

    return flights_json;
}

QJsonObject GetData::getFlightId(int &flight_id)
{
    QJsonObject flight;
    QString request;
    request = "select * from Flights inner join Plane on Flights.flight_id=Plane.plane_id where flights.flight_id=";
    request += QString::number(flight_id);
    QSqlDatabase db = QSqlDatabase::database("BOOKINGS");
    QSqlQuery query(request, db);

    while(query.next())
    {
        int flight_id = query.value(0).toInt();
        int company_id = query.value(2).toInt();
        QString depart_city = query.value(3).toString();
        QString arrival_city = query.value(4).toString();
        QString depart_date = query.value(5).toString();
        QString depart_time = query.value(6).toString();
        QString arrival_date = query.value(7).toString();
        QString arrival_time = query.value(8).toString();
        int plane_id = query.value(9).toInt();
        QString model = query.value(10).toString();
        QString seat_row = query.value(11).toString();
        QString seat_column = query.value(12).toString();
        QString acquisition_date = query.value(13).toString();
        flight["flight_id"] = flight_id;
        flight["company_id"] = company_id;
        flight["plane_id"] = plane_id;
        flight["planeModel"] = model;
        flight["numberOfSeatRow"] = seat_row;
        flight["numberOfSeatColumn"] = seat_column;
        flight["acquisitionDate"] = acquisition_date;
        flight["departureCity"] = depart_city;
        flight["arrivalCity"] = arrival_city;
        flight["departureDate"] = depart_date;
        flight["departureTime"] = depart_time;
        flight["arrivalDate"] = arrival_date;
        flight["arrivalTime"] = arrival_time;
    }

    return flight;
}

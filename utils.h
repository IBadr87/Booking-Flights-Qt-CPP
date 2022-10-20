#ifndef UTILS_H
#define UTILS_H

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QByteArray>
#include <QSqlQuery>

void printJson(QJsonObject& obj);
int connectDatabase(QString path, QString database_name);
QJsonObject convert_array_json(QByteArray arr);
void jsonConfig(QString &path, QJsonObject&, QJsonObject&, QJsonObject&, QJsonObject&, QJsonObject&);
#endif // UTILS_H








// main function
//    QString sFile = "/Users/djophant/Downloads/DataBase.s3db";
//       if (QFile::exists(sFile))
//       {
//           QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","BOOKINGS");
//           db.setDatabaseName(sFile);
//           if (db.open() == false)
//               return -1;
//       }


// test class getData (get
//    GetData* c = new GetData();
//    QJsonObject obj;
//    int ab = 1;
//    obj = c->getFlightId(ab);
//    printJson(obj);



// test class postdata
//    QJsonObject reservation;
//    reservation = {{"customer_id", "3"}, {"flight_id", "2"}, {"firstNamePassenger", "Burpee"}, {"lastNamePassenger", "floor"}, {"reservationTime", "2022/09/05 11:00:00"},
//                   {"reservationCanceled", "yes"}, {"seatRowNumber", "3"}, {"seatColumnNumber", "A"}, {"uuid", "1234-Z334-234Z-190I-23"}};
//    PostData* p = new PostData();
//    p->postReservation(reservation);


// test class UpdateData
//    UpdateData* d = new UpdateData();
////    QJsonObject customer_2;
//    QJsonObject reservation_2;
////    customer_2 = {{"customer_id", 1}, {"passport_id", "A5426975425"}, {"lastName", "Juve"}, {"firstName", "Turin"}, {"email", "jse@gmail.com"}, {"telephone", "01233214"} };
//    reservation_2 = {
//        {"reservation_id", 1},
//        {"uuid", "12R5-3R5T-23B6"},
//        {"customer_id", 2},
//        {"flight_id", 1},
//        {"reservationTime", "25/12/2022 11:00"},
//        {"reservationCanceled", "yes"},
//        {"seatRowNumber", 3},
//        {"seatColumnNumber" , "E"},
//    };
//    qDebug() << reservation_2["reservationTime"].toString();

//    d->updateReservation(reservation_2);

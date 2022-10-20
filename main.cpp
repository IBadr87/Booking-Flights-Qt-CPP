#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHttpServer>
#include <QFile>
#include "getdata.h"
#include "postdata.h"
#include "updatedata.h"
#include "deletedata.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // connect to the database
    QString db_path = "C:/Users/ibrah/OneDrive/Desktop/Qt/DataBase.s3db";
    QString database_name = "BOOKINGS";
    qDebug() << connectDatabase(db_path, database_name);


    //Begin
    QJsonObject customerUrl, flightUrl, planeUrl, reservationUrl, companyUrl;
    int serverPort = 8585;


    QHttpServer server;
    GetData *controller_get = new GetData();
    PostData *controller_post = new PostData();
    UpdateData *controller_put = new UpdateData();
    DeleteData *controller_delete = new DeleteData();


    /*
     * read what is in the database with the GET rest API
    */
    // customers Get
    server.route("/Customer", [&] (const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::GET)
        {
            return controller_get->getCustomerAll();
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    server.route("/Customer/<arg>", [&] (int user_id, const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::GET)
        {
            return controller_get->getCustomerId(user_id);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    // company Get
    server.route("/Company", [&] (const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::GET)
        {
            return controller_get->getCompanyAll();
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    server.route("/Company/<arg>", [&] (int company_id, const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::GET)
        {
            return controller_get->getCompanyId(company_id);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    // Reservations Get
    server.route("/Reservation/Flights/<arg>", [&] (int flight_id, const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::GET)
        {
            return controller_get->getReservationFlightId(flight_id);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    server.route("/Reservation/Customer/<arg>", [&] (int user_id, const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::GET)
        {
            return controller_get->getReservationCustomerId(user_id);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    // Plane Get
    server.route("/Plane", [&] (const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::GET)
        {
            return controller_get->getPlaneAll();
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    server.route("/Plane/<arg>", [&] (int plane_id, const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::GET)
        {
            return controller_get->getPlaneId(plane_id);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    // flight Get
    server.route("/Flights", [&] (const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::GET)
        {
            return controller_get->getFlightAll();
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    server.route("/Flights/<arg>", [&] (int flight_id, const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::GET)
        {
            return controller_get->getFlightId(flight_id);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    /*
     * Delete to the database using the DELETE method
    */
    // customer delete
    server.route("/Customer/delete/<arg>", [&] (int user_id, const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::DELETE)
        {
            return controller_delete->deleteCustomer(user_id);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    // reservation delete
    server.route("/Reservation/delete/<arg>", [&] (int reservation_id, const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::DELETE)
        {
            return controller_delete->deleteReservation(reservation_id);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    /*
     * Write to the database using the POST method
    */
    // customer post
    server.route("/Customer/add", [&] (const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::POST)
        {
            QJsonObject customer = convert_array_json(request.body());
            controller_post->postCustomer(customer);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    // reservation post
    server.route("/Reservation/add", [&] (const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::POST)
        {
            QJsonObject reservation = convert_array_json(request.body());
            controller_post->postReservation(reservation);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    /*
     * Write to the database using the POST method
    */
    // update post
    server.route("/Customer/update", [&] (const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::PUT)
        {
            QJsonObject customer = convert_array_json(request.body());
            controller_put->updateCustomer(customer);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    // reservation post
    server.route("/Reservation/update", [&] (const QHttpServerRequest &request){
        if(request.method() == QHttpServerRequest::Method::PUT)
        {
            QJsonObject reservation = convert_array_json(request.body());
            controller_put->updateReservation(reservation);
        }
        return QJsonObject{
            {"status", "false"}
        };
    });

    qDebug() << server.listen(QHostAddress::Any, serverPort);

//    GetData *get = new GetData();
//    QJsonObject obj;
//    int ab = 7;
//    obj = get->getReservationCustomerId(ab);
//    printJson(obj);

    return a.exec();
}

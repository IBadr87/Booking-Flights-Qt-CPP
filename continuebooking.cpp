#include "continuebooking.h"
#include "ui_continuebooking.h"
#include "bookingflights.h"

ContinueBooking::ContinueBooking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContinueBooking)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    mUrlServer = "http://127.0.0.1:8585";

    BookingFlights *bookFlightId = new BookingFlights;
    bookFlightId->setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->pbConfirm,SIGNAL(clicked(bool)),this,SLOT(pbConfirmClicked()));
    //connect(ui->CB_SelPass,SIGNAL());
    connect(bookFlightId, SIGNAL(flightIdCatch(int)),this,SLOT(flightIdCatched(int)));
    //bookFlightId->setModal(true);//use of modal window instead of exec()
    //bookFlightId->show();
}

ContinueBooking::~ContinueBooking()
{
    delete ui;
}

/**
 * \brief: add customer flight reservation
 * \param: flightid: flight id, firstName: passenger's first name, lastName: passenger's last name,
 * \param: row: line number of seat, column: column number of seat, canceled: reservation done?
 * \result: have new reservation added to the table of database
*/
void ContinueBooking::addReservation(int flightid, int customerid, QString firstName, QString lastName,
                                              int row, QString column)
{
    QString uuid = QUuid::createUuid().toString().replace("{","").replace("}",""); //.toString();
    qDebug() << uuid;

    QString dateTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    qDebug() << dateTime;

    QString canceled = "false";

    QJsonObject jsonObject;
    jsonObject["flight_id"] = QString::number(flightid);
    jsonObject["customer_id"] =QString::number(customerid);
    jsonObject["uuid"] = uuid;
    jsonObject["firstNamePassenger"] = firstName;
    jsonObject["lastNamePassenger"] = lastName;
    jsonObject["reservationTime"] = dateTime;
    jsonObject["reservationCanceled"] = canceled;
    jsonObject["seatRowNumber"] = QString::number(row);
    jsonObject["seatColumnNumber"] = column;
    QJsonDocument doc(jsonObject);
    QByteArray b = doc.toJson();
    QNetworkReply *reply = manager->post(QNetworkRequest(QUrl(mUrlServer+"/Reservation/add")),b);
    connect(reply,SIGNAL(readyRead()),this,SLOT(reservationAdded()));
}

/**
 * \brief: find customer in the database
 * \param: id, the customer identifier
 * \result: show the custustomer information
*/
void ContinueBooking::getCustomer(int id)
{
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(mUrlServer+"/Customer/"+QString::number(id))));
                                                    //QUrl("http://127.0.0.1:8585/customer/"+QString::number(id)))
    connect(reply,SIGNAL(readyRead()),this,SLOT(customerReceived()));
}

/**
 * \brief: get customers list out of the database
 * \param: no parameter in the entry
 * \result: show list of customers specially their customer id, firstname and last name
*/
void ContinueBooking::getCustomers()
{
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(mUrlServer+"/Customer")));
    connect(reply,SIGNAL(readyRead()),this,SLOT(customersReceived()));
}

/*SLOTS*/
void ContinueBooking::reservationAdded()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    qDebug() << reply->readAll() << "Error:" << reply->errorString();
    delete reply;
}

/**
 * \brief: slots functions to know when request to webserver are received correctly
 * \brief: and reply is correct without error
*/
// about customers
void ContinueBooking::customerReceived()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    if (reply->error() == QNetworkReply::NoError)
    {
        //QByteArray b = reply->readAll();
        qDebug() << reply->readAll();
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }
    delete reply;
}

void ContinueBooking::customersReceived()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    if (reply->error() == QNetworkReply::NoError)
    {
        //QByteArray b = reply->readAll();
        qDebug() << reply->readAll();
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }
    delete reply;
}

void ContinueBooking::pbConfirmClicked()
{
    //if (ui->lePassengerFirst->isModified() && ui->lePassengerLast->isModified())
    //{
        int flightid = ui->leFlightID->text().toInt();
        int customerid = ui->leCustomerID->text().toInt();
        QString firstName = ui->lePassengerFirst->text();
        QString lastName = ui->lePassengerLast->text();
        int row = ui->leSeatRow->text().toInt();
        QString col = ui->leSeatCol->text();
        addReservation(flightid, customerid, firstName, lastName, row, col);
    //}
    //else
    //{
    //    qDebug() << "customer selected";
        //}
}

//slot to catch data from bookingflights
void ContinueBooking::flightIdCatched(int flightId)
{
    //ui->leFlightID->setReadOnly(true);
    ui->leFlightID->setText(QString::number(flightId));
}

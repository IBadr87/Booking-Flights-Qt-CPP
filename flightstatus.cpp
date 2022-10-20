#include "flightstatus.h"
#include "ui_flightstatus.h"

FlightStatus::FlightStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlightStatus)
{
    manager = new QNetworkAccessManager(this);
    mUrlServer = "http://127.0.0.1:8585";

    ui->setupUi(this);

    connect(ui->PB_Search, SIGNAL(clicked()), this, SLOT(pbSearchClicked()));
    connect(ui->PB_Cancel, SIGNAL(clicked()), this, SLOT(pbCancelClicked()));
}

FlightStatus::~FlightStatus()
{
    delete ui;
}

void FlightStatus::getReservation(int Customer_id)
{
    qDebug() << "je suis dans get reservation";
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(mUrlServer+"/Reservation/Customer/"+QString::number(Customer_id))));
    connect(reply,SIGNAL(readyRead()),this,SLOT(ReservationReceived()));
}

void FlightStatus::cancelReservation(int reservation_id)
{
    QNetworkReply *reply = manager->deleteResource(QNetworkRequest(QUrl(mUrlServer+"/Reservation/delete/"+QString::number(reservation_id))));
    connect(reply,SIGNAL(readyRead()),this,SLOT(ReservationCancelled()));
}

void FlightStatus::ReservationReceived()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    qDebug() << "je suis dans reservation recieved";

    if (reply->error() == QNetworkReply::NoError)
    {
        ui->TW_Flight->clear();
        ui->TW_Flight->setRowCount(0);
        ui->TW_Flight->setColumnCount(10);
        ui->TW_Flight->setHorizontalHeaderLabels(QStringList() << "Customer ID" << "Flight ID" << "UUID" << "First Name" << "Last Name" << "Reservation Time" << "Cancel Reservation" << "Seat Row Number" << "Seat Column Number" << "Reservation ID");

        QByteArray b = reply->readAll();
        qDebug() << b;
        QJsonObject o = QJsonDocument::fromJson(b).object();
        qDebug() << o;
        QJsonArray a = o["data"].toArray();

        int customer_id = ui->LE_CustoID->text().toInt();

        for(int i =0; i < a.count(); i++)
        {
            QJsonObject customer = a[i].toObject();
            QJsonArray reservations = customer["reservations"].toArray();
            QJsonObject flight = customer["flights"].toObject();

            int flight_id = flight["flight_id"].toInt();
            for(int j = 0; j < reservations.count(); j++)
            {
                QJsonObject reservation = reservations[j].toObject();
                QString uuid = reservation["uuid"].toString();
                QString firstName = reservation["firstNamePassenger"].toString();
                QString lastName = reservation["lastNamePassenger"].toString();
                QString time = reservation["reservationTime"].toString();
                QString canceled = reservation["reservationCanceled"].toString();
                int row = reservation["seatRowNumber"].toInt();
                int reservation_id = reservation["reservation_id"].toInt();
                QString column = reservation["seatColumnNumber"].toString();

                ui->TW_Flight->setRowCount(ui->TW_Flight->rowCount()+1);

                ui->TW_Flight->setCellWidget(ui->TW_Flight->rowCount()-1,0,new QLabel(QString::number(customer_id)));
                ui->TW_Flight->setCellWidget(ui->TW_Flight->rowCount()-1,1,new QLabel(QString::number(flight_id)));
                ui->TW_Flight->setCellWidget(ui->TW_Flight->rowCount()-1,2,new QLabel(uuid));
                ui->TW_Flight->setCellWidget(ui->TW_Flight->rowCount()-1,3,new QLabel(firstName));
                ui->TW_Flight->setCellWidget(ui->TW_Flight->rowCount()-1,4,new QLabel(lastName));
                ui->TW_Flight->setCellWidget(ui->TW_Flight->rowCount()-1,5,new QLabel(time));
                ui->TW_Flight->setCellWidget(ui->TW_Flight->rowCount()-1,6,new QLabel(canceled));
                ui->TW_Flight->setCellWidget(ui->TW_Flight->rowCount()-1,7,new QLabel(QString::number(row)));
                ui->TW_Flight->setCellWidget(ui->TW_Flight->rowCount()-1,8,new QLabel(column));
                ui->TW_Flight->setCellWidget(ui->TW_Flight->rowCount()-1,9,new QLabel(QString::number(reservation_id)));
            }
        }
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }

    delete reply;
}

void FlightStatus::ReservationCancelled()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    qDebug() << reply->readAll() << "Error:" << reply->errorString();
    delete reply;
}

void FlightStatus::pbSearchClicked()
{
    int customer_id = ui->LE_CustoID->text().toInt();
    qDebug() << "customer_id searche button clicked" << customer_id;
    getReservation(customer_id);
}

void FlightStatus::pbCancelClicked()
{
    int reservation_id = ui->LE_RerservID->text().toInt();
    cancelReservation(reservation_id);
}



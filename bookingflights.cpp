#include "bookingflights.h"
#include "ui_bookingflights.h"
#include "SeatWidget.h"
#include "continuebooking.h"

BookingFlights::BookingFlights(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookingFlights)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    mUrlServer = "http://127.0.0.1:8585";
    mByte = NULL;

    connect(ui->Pb_Continue,SIGNAL(clicked(bool)), this, SLOT(PBContinueClicked()));

    connect(ui->pbFlightsAll, SIGNAL(clicked()), this, SLOT(pbFlightAllClicked()));
    connect(ui->TW_Affiche,SIGNAL(clicked(const QModelIndex &)), this, SLOT(twCellIsClicked(const QModelIndex &)));
    connect(ui->pbSearch,SIGNAL(clicked()),this,SLOT(pbSearchClicked()));

}

BookingFlights::~BookingFlights()
{
    delete ui;
}

//about flights
/**
 * \brief: get all flights
 * \result: have the list of flights from the database
*/
void BookingFlights::getAllFlights()
{
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(mUrlServer+"/Flights")));
    connect(reply,SIGNAL(readyRead()),this,SLOT(allFlightsReceived()));
}

/**
 * \brief: get filght
 * \param: id: flight id from the flights table of database
 * \result: have information about a flight from the database
*/
void BookingFlights::getFlight(int id)
{
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(mUrlServer+"/Flights/"+QString::number(id))));
    connect(reply,SIGNAL(readyRead()),this,SLOT(flightReceived()));
}

void BookingFlights::searchFlight()
{
    QString departureCity = ui->LE_From->text();
    QString arrivalCity = ui->LE_To->text();

    QNetworkReply *reply = (QNetworkReply *)sender();
    if (reply->error() == QNetworkReply::NoError)
    {
        ui->TW_Affiche->clear();
        ui->TW_Affiche->setColumnCount(8);
        ui->TW_Affiche->setHorizontalHeaderLabels(QStringList() << "Company Name"<< "Fligth ID"<<
                                                  "Departure City" << "Departure Date" << "Depature Time" <<
                                                  "Arrival City" << "Arrival Date" << "Arrival Time");
        ui->TW_Affiche->setRowCount(0);

        QByteArray b = reply->readAll();
        qDebug() << "byte array b:" << b;
        //QList<QString> flightList;
        QJsonObject o = QJsonDocument::fromJson(b).object();
        qDebug() << "json object o:" << o;
        QJsonArray a = o["allFlights"].toArray();
        qDebug() << "json array a:" << a;
        for (int i = 0; i < a.count(); i++)
        {
            QJsonObject flights = a[i].toObject();
            int idF = flights["flight_id"].toInt();
            QString dCity = flights["departureCity"].toString();
            QString dDate = flights["departureDate"].toString();
            QString dTime = flights["departureTime"].toString();
            QString aCity = flights["arrivalCity"].toString();
            QString aDate = flights["arrivalDate"].toString();
            QString aTime = flights["arrivalTime"].toString();

            int idCompany = flights["company_id"].toInt();
            //int idCompany = idC.toInt();
            QString cName;

            getCompanies();

            qDebug() << "byte array bc:" << mByte;
            QJsonObject oc = QJsonDocument::fromJson(mByte).object();
            qDebug() << "json object oc:" << oc;
            QJsonArray ac = oc["allCompany"].toArray();
            qDebug() << "json array ac:" << ac;
            for (int j = 0; j < ac.count(); j++)
            {
                QJsonObject companies = ac[j].toObject();
                if (companies["company_id"].toInt() == idCompany)
                {
                    cName = companies["companyName"].toString();
                    qDebug() << "cName:" << cName;
                }
            }

            if (dCity == departureCity && aCity == arrivalCity)
            {
                ui->TW_Affiche->setRowCount(ui->TW_Affiche->rowCount()+1);

                ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,0,new QLabel(cName));
                ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,1,new QLabel(QString::number(idF)));
                ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,2,new QLabel(dCity));
                ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,3,new QLabel(dDate));
                ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,4,new QLabel(dTime));
                ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,5,new QLabel(aCity));
                ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,6,new QLabel(aDate));
                ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,7,new QLabel(aTime));
            }
            else
            {
                qDebug() << "continue";
            }
        }
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }
    delete reply;
}

void BookingFlights::displayFlights()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    if (reply->error() == QNetworkReply::NoError)
    {
        ui->TW_Affiche->clear();
        ui->TW_Affiche->setColumnCount(8);
        ui->TW_Affiche->setHorizontalHeaderLabels(QStringList() << "Company Name"<< "Fligth ID"<<
                                                  "Departure City" << "Departure Date" << "Depature Time" <<
                                                  "Arrival City" << "Arrival Date" << "Arrival Time");
        ui->TW_Affiche->setRowCount(0);

        QByteArray b = reply->readAll();
        qDebug() << "byte array b:" << b;
        QJsonObject o = QJsonDocument::fromJson(b).object();
        qDebug() << "json object o:" << o;
        QJsonArray a = o["allFlights"].toArray();
        qDebug() << "json array a:" << a;
        for (int i = 0; i < a.count(); i++)
        {
            QJsonObject flights = a[i].toObject();
            int idF = flights["flight_id"].toInt();
            QString dCity = flights["departureCity"].toString();
            QString dDate = flights["departureDate"].toString();
            QString dTime = flights["departureTime"].toString();
            QString aCity = flights["arrivalCity"].toString();
            QString aDate = flights["arrivalDate"].toString();
            QString aTime = flights["arrivalTime"].toString();

            int idCompany = flights["company_id"].toInt();
            //int idCompany = idC.toInt();
            QString cName;

            getCompanies();

            qDebug() << "byte array bc:" << mByte;
            QJsonObject oc = QJsonDocument::fromJson(mByte).object();
            qDebug() << "json object oc:" << oc;
            QJsonArray ac = oc["allCompany"].toArray();
            qDebug() << "json array ac:" << ac;
            for (int j = 0; j < ac.count(); j++)
            {
                QJsonObject companies = ac[j].toObject();
                if (companies["company_id"].toInt() == idCompany)
                {
                    cName = companies["companyName"].toString();
                    qDebug() << "cName:" << cName;
                }
            }

            ui->TW_Affiche->setRowCount(ui->TW_Affiche->rowCount()+1);

            ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,0,new QLabel(cName));
            ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,1,new QLabel(QString::number(idF)));
            ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,2,new QLabel(dCity));
            ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,3,new QLabel(dDate));
            ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,4,new QLabel(dTime));
            ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,5,new QLabel(aCity));
            ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,6,new QLabel(aDate));
            ui->TW_Affiche->setCellWidget(ui->TW_Affiche->rowCount()-1,7,new QLabel(aTime));
        }
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }
    delete reply;
}


//about companies
/**
 * \brief: get all companies
 * \result: have the list of companies from the database
*/
void BookingFlights::getCompanies()
{
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(mUrlServer+"/Company")));
    connect(reply,SIGNAL(readyRead()),this,SLOT(companiesReceived()));
}

/*SLOTS*/

// about flights
void BookingFlights::allFlightsReceived()
{
    QString departureCity = ui->LE_From->text();
    QString arrivalCity = ui->LE_To->text();

    if (departureCity.isEmpty() && arrivalCity.isEmpty())
    {
        displayFlights();
    }
    else
    {
        searchFlight();
    }
}

void BookingFlights::flightReceived()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    if (reply->error() == QNetworkReply::NoError)
    {
        ui->TW_Affiche->clear();
        ui->TW_Affiche->setRowCount(12);
        ui->TW_Affiche->setVerticalHeaderLabels(QStringList() << "Fligth ID"<< "Company ID"<<
                                                "Plane ID" << "Plane Model" << "Nombre of Seat" << "Plan Acquisition Date" <<
                                                "Departure City" << "Arrival City" << "Departure Date" <<
                                                "Departure Time" << "Arrival Date" << "Arrival Time");
        ui->TW_Affiche->setColumnCount(0);

        QByteArray b = reply->readAll();
        qDebug() << "byte array b:" << b;
        QJsonObject o = QJsonDocument::fromJson(b).object();
        int row = o["numberOfSeatRow"].toInt();
        int col = o["numberOfSeatColumn"].toInt();
        qDebug() << "row:" << row;
        qDebug() << "col:" << col;
        QString idF = o["flight_id"].toString();
        QString idC = o["company_id"].toString();
        QString idP = o["plane_id"].toString();
        QString pMod = o["planeModel"].toString();
        int capacity = row*col;
        QString acDate = o["acquisitionDate"].toString();
        QString dCity = o["departureCity"].toString();
        QString aCity = o["arrivalCity"].toString();
        QString dDate = o["departureDate"].toString();
        QString dTime = o["departureTime"].toString();
        QString aDate = o["arrivalDate"].toString();
        QString aTime = o["arrivalTime"].toString();

        ui->TW_Affiche->setColumnCount(ui->TW_Affiche->columnCount()+1);

        ui->TW_Affiche->setCellWidget(0,ui->TW_Affiche->columnCount()-1,new QLabel(idF));
        ui->TW_Affiche->setCellWidget(1,ui->TW_Affiche->columnCount()-1,new QLabel(idC));
        ui->TW_Affiche->setCellWidget(2,ui->TW_Affiche->columnCount()-1,new QLabel(idP));
        ui->TW_Affiche->setCellWidget(3,ui->TW_Affiche->columnCount()-1,new QLabel(pMod));
        ui->TW_Affiche->setCellWidget(4,ui->TW_Affiche->columnCount()-1,new QLabel(QString::number(capacity)));
        ui->TW_Affiche->setCellWidget(5,ui->TW_Affiche->columnCount()-1,new QLabel(acDate));
        ui->TW_Affiche->setCellWidget(6,ui->TW_Affiche->columnCount()-1,new QLabel(dCity));
        ui->TW_Affiche->setCellWidget(7,ui->TW_Affiche->columnCount()-1,new QLabel(aCity));
        ui->TW_Affiche->setCellWidget(8,ui->TW_Affiche->columnCount()-1,new QLabel(dDate));
        ui->TW_Affiche->setCellWidget(9,ui->TW_Affiche->columnCount()-1,new QLabel(dTime));
        ui->TW_Affiche->setCellWidget(10,ui->TW_Affiche->columnCount()-1,new QLabel(aDate));
        ui->TW_Affiche->setCellWidget(11,ui->TW_Affiche->columnCount()-1,new QLabel(aTime));
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }
    delete reply;
}

void BookingFlights::companiesReceived()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray b = reply->readAll();
        mByte = b;
        qDebug() << "companiesReceived reply:" << mByte;
    }
    else
    {
         qDebug() << "Error:" << reply->errorString();
    }
    delete reply;
}


void BookingFlights::PBContinueClicked()
{
    ContinueBooking c(this);
    c.exec();
}

void BookingFlights::pbSearchClicked()
{
    getAllFlights();
}

void BookingFlights::pbFlightAllClicked()
{
    getAllFlights();
}

void BookingFlights::twCellIsClicked(const QModelIndex &index)
{
    int id = 0;
    if (index.isValid())
    {
        id = index.data().toInt();
    }
    qDebug() << "flight id:" << id;
    emit flightIdCatch(id);
    getFlight(id);
}

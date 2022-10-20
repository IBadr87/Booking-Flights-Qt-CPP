#ifndef BOOKINGFLIGHTS_H
#define BOOKINGFLIGHTS_H

#include <QDialog>
#include "SeatWidget.h"
#include "continuebooking.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QDateTime>
#include <QUuid>
#include <QJsonArray>
#include <QModelIndex>

namespace Ui {
class BookingFlights;
}

class BookingFlights : public QDialog
{
    Q_OBJECT

public:
    explicit BookingFlights(QWidget *parent = nullptr);
    ~BookingFlights();

    void getAllFlights();
    void getFlight(int id);

    void searchFlight();
    void displayFlights();

    void getCompanies();
    QByteArray getmByte() { return mByte;};

signals:
    void flightIdCatch(int);

private slots:
    void allFlightsReceived();
    void flightReceived();

    void companiesReceived();

    //QPushButton clicked
    void PBContinueClicked();
    void pbSearchClicked();
    void pbFlightAllClicked();
    void twCellIsClicked(const QModelIndex &);

private:
    Ui::BookingFlights *ui;
    QNetworkAccessManager *manager;
    QString  mUrlServer;
    QByteArray mByte;
};

#endif // BOOKINGFLIGHTS_H

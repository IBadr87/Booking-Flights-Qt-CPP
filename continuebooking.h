#ifndef CONTINUEBOOKING_H
#define CONTINUEBOOKING_H

#include <QDialog>
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
class ContinueBooking;
}

class ContinueBooking : public QDialog
{
    Q_OBJECT

public:
    explicit ContinueBooking(QWidget *parent = nullptr);
    ~ContinueBooking();

    void addReservation(int flightid, int customerid, QString firstName, QString lastName, int row, QString column);
    void getCustomer(int id);
    void getCustomers();

private slots:
    void reservationAdded();
    void customerReceived();
    void customersReceived();

    void pbConfirmClicked();

    void flightIdCatched(int);

private:
    Ui::ContinueBooking *ui;
    QNetworkAccessManager *manager;
    QString  mUrlServer;
};

#endif // CONTINUEBOOKING_H

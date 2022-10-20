#ifndef FLIGHTSTATUS_H
#define FLIGHTSTATUS_H

#include <QDialog>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfoList>
#include <QDir>
#include <QModelIndex>
#include <QJsonArray>

namespace Ui
{
class FlightStatus;
}

class FlightStatus : public QDialog
{
    Q_OBJECT

public:
    explicit FlightStatus(QWidget *parent = nullptr);
    ~FlightStatus();

    void getReservation(int Customer_id);
    void cancelReservation(int Customer_id);

private slots:
    void ReservationReceived();
    void ReservationCancelled();

    void pbSearchClicked();
    void pbCancelClicked();

private:
    Ui::FlightStatus *ui;
    QNetworkAccessManager *manager;
    QString  mUrlServer;
};

#endif // FLIGHTSTATUS_H

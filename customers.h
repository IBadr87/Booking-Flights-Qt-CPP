#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <QDialog>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfoList>
#include <QDir>
#include <QModelIndex>

namespace Ui
{
class Customers;
}

class Customers : public QDialog
{
    Q_OBJECT

public:
    explicit Customers(QWidget *parent = nullptr);
    ~Customers();

    void getCustomer(int id);
    void getCustomers();
    void addCustomer(QString nom, QString prenom, QString passport, QString email, QString phone);
    void updateCustomer(int id, QString nom, QString prenom, QString passport, QString email, QString phone);
    void deleteCustomer(int id);

private slots:
    void customerReceived();
    void customersReceived();
    void customerAdded();
    void customerUpdated();
    void customerDeleted();

    void pbFindClicked();
    void pbDisplayAllClicked();
    void pbAddClicked();
    void pbModifyClicked();
    void pbDeleteClicked();

private:
    Ui::Customers *ui;
    QNetworkAccessManager *manager;
    QString  mUrlServer;
};

#endif // CUSTOMERS_H

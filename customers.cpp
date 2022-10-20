#include "customers.h"
#include "ui_customers.h"
#include <QJsonArray>
#include <QSqlQueryModel>

Customers::Customers (QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Customers)
{
    manager = new QNetworkAccessManager(this);
    mUrlServer = "http://127.0.0.1:8585";

    ui->setupUi(this);

    connect(ui->PB_Find, SIGNAL(clicked()), this, SLOT(pbFindClicked()));
    connect(ui->PB_DisplayAll, SIGNAL(clicked()), this, SLOT(pbDisplayAllClicked()));
    connect(ui->PB_Add, SIGNAL(clicked()), this, SLOT(pbAddClicked()));
    connect(ui->PB_Modify, SIGNAL(clicked()), this, SLOT(pbModifyClicked()));
    connect(ui->PB_Delete, SIGNAL(clicked()), this, SLOT(pbDeleteClicked()));
}

Customers::~Customers()
{
    delete ui;
}

void Customers::getCustomer(int id)
{
    QUrl u(mUrlServer+"/Customer/"+QString::number(id));
    qDebug() << "getCustomer" << u;

    QNetworkReply *reply = manager->get(QNetworkRequest(u));
    reply->setProperty("id",id);
    connect(reply,SIGNAL(readyRead()),this,SLOT(customerReceived()));
}

/*
 * \brief: get customers list out of the database
 * \param: no parameter in the entry
 * \result: show list of customers specially their customer id, firstname and last name
*/

void Customers::getCustomers()
{
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(mUrlServer+"/Customer")));
    connect(reply,SIGNAL(readyRead()),this,SLOT(customersReceived()));
}

/*
 * \brief: add customer to the customers table of the database
 * \param: nom: lastname, prenom: firstname, passport: passport_id, email: email adresse, telephone: phone number
 * \result: get customer added to the database
*/

void Customers::addCustomer(QString nom, QString prenom, QString passport, QString email, QString phone)
{
    QJsonObject jsonObject;
    jsonObject["lastName"] = nom;
    jsonObject["firstName"] = prenom;
    jsonObject["passport_id"] = passport;
    jsonObject["email"] = email;
    jsonObject["telephone"] = phone;

    QJsonDocument doc(jsonObject);
    QByteArray b = doc.toJson();
    QNetworkReply *reply = manager->post(QNetworkRequest(QUrl(mUrlServer+"/Customer/add")),b);
    connect(reply,SIGNAL(readyRead()),this,SLOT(customerAdded()));
}

/*
 * \brief: update customer information in the customers table of the database
 * \param: nom: lastname, prenom: firstname, passport: passport_id, email: email adresse, telephone: phone number
 * \result: get customer updated in the database
*/

void Customers::updateCustomer(int id, QString nom, QString prenom, QString passport, QString email, QString phone)
{
    QJsonObject jsonObject;
    jsonObject["customer_id"] = id;
    jsonObject["lastName"] = nom;
    jsonObject["firstName"] = prenom;
    jsonObject["passport_id"] = passport;
    jsonObject["email"] = email;
    jsonObject["telephone"] = phone;

    QJsonDocument doc(jsonObject);
    QByteArray b = doc.toJson();
    QNetworkReply *reply = manager->put(QNetworkRequest(QUrl(mUrlServer+"/Customer/update")),b);
    connect(reply,SIGNAL(readyRead()),this,SLOT(customerUpdated()));
}

/*
 * \brief: remove customer in the customers table of the database
 * \param: id: customer id coresponding to the ref. in the table
 * \result: customer deleted
*/

void Customers::deleteCustomer(int id)
{
    QNetworkReply *reply = manager->deleteResource(QNetworkRequest(QUrl(mUrlServer+"/Customer/delete/"+QString::number(id))));
    connect(reply,SIGNAL(readyRead()),this,SLOT(customerDeleted()));
}

/*
   \brief: slots to know when request to webserver are received correctly
*/

void Customers::customerReceived()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    QByteArray b = reply->readAll();

    //int idCustomer = reply->property("customer_id").toInt();

    if (reply->error() == QNetworkReply::NoError)
    {
        ui->TW_Display->clear();
        ui->TW_Display->setRowCount(0);
        ui->TW_Display->setColumnCount(6);
        ui->TW_Display->setHorizontalHeaderLabels(QStringList() << "ID" << "Passport" << "Last Name" << "First Name" << "Email" << "Telephone");

        qDebug() << b;
        QJsonObject o = QJsonDocument::fromJson(b).object();
        qDebug() << o;

        ui->TW_Display->setRowCount(ui->TW_Display->rowCount()+1);

        ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,0,new QLabel(QString::number(o["customer_id"].toInt())));
        ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,1,new QLabel(o["passport_id"].toString()));
        ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,2,new QLabel(o["lastName"].toString()));
        ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,3,new QLabel(o["firstName"].toString()));
        ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,4,new QLabel(o["email"].toString()));
        ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,5,new QLabel(o["Telephone"].toString()));
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }

    //emit customerOk(idCustomer,b);

    delete reply;
}

void Customers::customersReceived()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    QByteArray b = reply->readAll();

    if (reply->error() == QNetworkReply::NoError)
    {
        ui->TW_Display->clear();
        ui->TW_Display->setRowCount(0);
        ui->TW_Display->setColumnCount(6);
        ui->TW_Display->setHorizontalHeaderLabels(QStringList() << "ID" << "Passport" << "Last Name" << "First Name" << "Email" << "Telephone");

        qDebug() << "byte array b:" << b;

        QJsonObject o = QJsonDocument::fromJson(b).object();
        qDebug() << "json object o:" << o;
        QJsonArray a = o["allCustomers"].toArray();
        qDebug() << "json array a:" << a;

        for (int i = 0; i < a.count(); i++)
        {
            QJsonObject allCustomer = a[i].toObject();
            int ID = allCustomer["customer_id"].toInt();
            QString Pass = allCustomer["passport_id"].toString();
            QString Last = allCustomer["lastName"].toString();
            QString First = allCustomer["firstName"].toString();
            QString Email = allCustomer["email"].toString();
            QString Tele = allCustomer["telephone"].toString();

            qDebug() << "ID:" << ID;
            ui->TW_Display->setRowCount(ui->TW_Display->rowCount()+1);

            ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,0,new QLabel(QString::number(ID)));
            ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,1,new QLabel(Pass));
            ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,2,new QLabel(Last));
            ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,3,new QLabel(First));
            ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,4,new QLabel(Email));
            ui->TW_Display->setCellWidget(ui->TW_Display->rowCount()-1,5,new QLabel(Tele));
        }
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }
    delete reply;
}

void Customers::customerAdded()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    qDebug() << reply->readAll() << "Error:" << reply->errorString();
    delete reply;
}

void Customers::customerUpdated()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    qDebug() << reply->readAll() << "Error:" << reply->errorString();
    delete reply;
}

void Customers::customerDeleted()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    qDebug() << reply->readAll() << "Error:" << reply->errorString();
    delete reply;
}

void Customers::pbFindClicked()
{
    int id = ui->LE_ID->text().toInt();
    getCustomer(id);

}

void Customers::pbDisplayAllClicked()
{    
    getCustomers();
}

void Customers::pbAddClicked()
{
    QString nom = ui->LE_LastName->text();
    QString prenom = ui->LE_FirstName->text();
    QString passport = ui->LE_Passport->text();
    QString email = ui->LE_Email->text();
    QString phone = ui->LE_Telephone->text();

    addCustomer(nom, prenom, passport, email, phone);

    if (nom.isEmpty() || prenom.isEmpty() || passport.isEmpty() || email.isEmpty() || phone.isEmpty())
    {
        return;
    }

/*
    const int row = ui->TW_Display->rowCount();
    ui->TW_Display->insertRow(row);
    ui->TW_Display->setHorizontalHeaderLabels(QStringList() << "ID" << "Passport" << "Last Name" << "First Name" << "Email" << "Telephone");
    ui->TW_Display->setItem(row, 1, new QTableWidgetItem(nom));
    ui->TW_Display->setItem(row, 2, new QTableWidgetItem(prenom));
    ui->TW_Display->setItem(row, 3, new QTableWidgetItem(passport));
    ui->TW_Display->setItem(row, 4, new QTableWidgetItem(email));
    ui->TW_Display->setItem(row, 5, new QTableWidgetItem(phone));
*/
}

void Customers::pbModifyClicked()
{
    int id = ui->LE_ID->text().toInt();
    QString nom = ui->LE_LastName->text();
    QString prenom = ui->LE_FirstName->text();
    QString passport = ui->LE_Passport->text();
    QString email = ui->LE_Email->text();
    QString telephone = ui->LE_Telephone->text();

    updateCustomer(id, nom, prenom, passport, email, telephone);
}

void Customers::pbDeleteClicked()
{
    //ui->TW_Display->removeRow(ui->TW_Display->currentRow());
    int id = ui->LE_ID->text().toInt();
    deleteCustomer(id);
}

#include "utils.h"


void printJson(QJsonObject &obj)
{
    QJsonDocument doc(obj);
    qDebug() << doc.toJson(QJsonDocument::Compact);
}



int connectDatabase(QString path, QString database_name)
{
       if (QFile::exists(path))
       {
           QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE",database_name);
           db.setDatabaseName(path);
           if (db.open() == false)
               return -1;
       }
       return 0;
}

QJsonObject convert_array_json(QByteArray arr)
{
    QJsonObject json_obj;
    if(arr.isEmpty())
        return json_obj;

    QJsonDocument itemDoc = QJsonDocument::fromJson(arr);
    QJsonObject new_json_obj = itemDoc.object();

    return new_json_obj;
}



void jsonConfig(QString &path_json, QJsonObject &customer, QJsonObject &company, QJsonObject &reserv,\
                QJsonObject &flight, QJsonObject &plane)
{
    QFile jsonFile(path_json);
    if (jsonFile.open(QFile::ReadOnly | QFile::Text))
        {
            QByteArray arr = jsonFile.readAll();
            QJsonDocument documentJSON = QJsonDocument::fromJson(arr);
            QJsonObject json_obj = documentJSON.object();
            customer = json_obj["customers"].toObject();
            company = json_obj["companies"].toObject();
            reserv = json_obj["reservations"].toObject();
            flight = json_obj["flights"].toObject();
            plane = json_obj["plane"].toObject();
            jsonFile.close();
        }
}

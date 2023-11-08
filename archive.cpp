#include "archive.h"
#include<QString>
#include<QDebug>
#include<QDate>
#include <QSqlError>
using namespace std;

Archive::Archive() {
    ID = 0;
    NOM="";
    TYPE = "";
    VERSION = "";
}

Archive::Archive(int id,  QString nom,  QDate dateHis,  QString type,  QString version)
{
    ID = id;
    NOM = nom;
    DATE_HIS = dateHis;
    TYPE = type;
    VERSION = version;
}

// Getters
int Archive::getID() const {
    return ID;
}

QString Archive::getNOM() const {
    return NOM;
}

QDate Archive::getDATE_HIS() const {
    return DATE_HIS;
}


QString Archive::getTYPE() const {
    return TYPE;
}

QString Archive::getVERSION() const {
    return VERSION;
}

// Setters
void Archive::setID(int id) {
    ID = id;
}

void Archive::setNOM(const QString& nom) {
    NOM = nom;
}

void Archive::setDATE_HIS(const QDate& date) {
    DATE_HIS = date;
}


void Archive::setTYPE(const QString& type) {
    TYPE = type;
}

void Archive::setVERSION(const QString& version) {
    VERSION = version;
}



bool Archive::ajouter() {


    QSqlQuery query;
    QString res=QString::number(ID);
         query.prepare("INSERT INTO ARCHIVE (ID, NOM, DATE_HIS, TYPE, VERSION)" "values (:ID, :NOM, :DATE_HIS, :TYPE, :VERSION)");
         query.bindValue(":ID", res);
         query.bindValue(":NOM", NOM);
         query.bindValue(":DATE_HIS", DATE_HIS);
         query.bindValue(":TYPE", TYPE);
         query.bindValue(":VERSION", VERSION);

         return query.exec();



}



bool Archive::supprimer(int ID) {
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    QString deleteQuery = "DELETE FROM ARCHIVE WHERE ID = :ID";
    query.prepare(deleteQuery);
    query.bindValue(":ID", ID);

    bool success = query.exec();

    if (!success) {
        qDebug() << "Error deleting record:" << query.lastError().text();
    }

    return success;
}


bool Archive::update(int ID, QString NOM, QDate DATE_HIS, QString TYPE, QString VERSION) {
    QSqlQuery query;
    query.prepare("UPDATE ARCHIVE SET NOM=:NOM, DATE_HIS=:DATE_HIS, TYPE=:TYPE, VERSION=:VERSION WHERE ID=:ID");
    query.bindValue(":NOM", NOM);
    query.bindValue(":DATE_HIS", DATE_HIS);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":VERSION", VERSION);
    query.bindValue(":ID", ID);
    return query.exec();
}




QSqlQueryModel * Archive::Afficher(){
    QSqlQueryModel * m=new QSqlQueryModel();
    m->setQuery("SELECT * from ARCHIVE");
    m->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    m->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    m->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_HIS"));
    m->setHeaderData(3,Qt::Horizontal,QObject::tr("TYPE"));
    m->setHeaderData(4,Qt::Horizontal,QObject::tr("VERSION"));


    return m;

}



vector<Archive> Archive::ListDesArchives(int ID){
    Archive a;
    vector<Archive> vecteurArchives;

    QSqlQuery query;
    query.prepare("SELECT * from ARCHIVE where ID!=:ID");
    query.bindValue(":ID",ID);

    if (query.exec()) {
        while(query.next()){
            a.setID(query.value("ID").toInt());
            a.setNOM(query.value("NOM").toString());
            a.setDATE_HIS(query.value("DATE_HIS").toDate());
            a.setTYPE(query.value("TYPE").toString());
            a.setVERSION(query.value("VERSION").toString());


            // Retrieve date as QDateTime and then convert it to QDate
            QDateTime dateTime = query.value("DATE").toDateTime();
            a.setDATE_HIS(dateTime.date());

            vecteurArchives.push_back(a);
        }
    }
    return vecteurArchives;
}

#ifndef Archive_H
#define Archive_H
#include<QString>
#include <QSqlQuery>
#include<QDate>
#include <QSqlQueryModel>
#include <vector>

using namespace std;

class Archive
{
public:
    // variables de l'entité


    int ID;
    QString NOM;
    QDate DATE_HIS;
    QString TYPE;
    QString VERSION;

    Archive();

    Archive(int id,  QString ,  QDate ,  QString ,  QString );



    int getID() const ;
    QString getNOM() const ;
    QDate getDATE_HIS() const ;
;
    QString getTYPE() const ;
    QString getVERSION() const ;

    void setID(int id);
    void setNOM(const QString& nom);
    void setDATE_HIS(const QDate& date);

    void setTYPE(const QString& type);
    void setVERSION(const QString& version);


    bool ajouter();
    bool supprimer(int ID);
    bool update(int ID, QString NOM, QDate DATE_HIS,QString TYPE,QString VERSION);
    QSqlQueryModel *Afficher();
    vector<Archive> ListDesArchives(int);
};


#endif // Archive_H

#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{  QSqlDatabase db;
public:
    Connection(); //constructeur

    bool createconnect();
    void closeconnection();
};

#endif // CONNECTION_H

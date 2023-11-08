#include "mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include "connection.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    bool test = c.createconnect();

    if (test)
    {
        w.show();
        qDebug() << "Database connected successfully!";

    }
    else
    {
        qDebug() << "Database connection failed!"; // Changed the message here

        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                    QObject::tr("Connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec();
}

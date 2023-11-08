#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "archive.h"
#include <QMessageBox>
#include <QDate>
#include <QRegularExpression>
#include <QUuid>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    selectedId = -1;
    etatformulaire = "add";
    endusavec = 0;


    // controle de saisie sur les champs


    ui->e_id->setValidator(new QIntValidator(0,9999999,this)) ;
    ui->e_nom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{1,20}"), this)); // les lettre seulement  entre 1 et 20
    ui->e_type->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{1,20}"), this)); // les lettre seulement  entre 1 et 20
    ui->e_version->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9_]{1,20}"), this)); // version accepter entre 1 et 20 caractéres composé des lettres et chiffres



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
        int id=ui->e_id->text().toInt();
    QString nom = ui->e_nom->text();


    QDateTime dateTime = ui->e_Date->dateTime();

    QString type = ui->e_type->text();
    QString version = ui->e_version->text();

    QDate convertedDate = dateTime.date(); // Get the date part

    qDebug() << "Date String: " << dateTime;
    qDebug() << "Converted Date: " << convertedDate.toString("dd-MMM-yy");


    // Vérifier si un champ est vide
       if (nom.isEmpty() || type.isEmpty() || version.isEmpty()) {
           QMessageBox::critical(nullptr, QObject::tr("Champs vides"),
               QObject::tr("Veuillez remplir tous les champs."), QMessageBox::Cancel);
           return; // Ne pas continuer avec l'opération d'ajout
       }


    Archive C(id,nom,convertedDate,type,version);
    bool test=C.ajouter();

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                    QObject::tr("Ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }


    ui->e_nom->clear();
    ui->e_Date->clear();
    ui->e_type->clear();
    ui->e_version->clear();

  setdata();


}
// Add comments and move setdata logic here if applicable
void MainWindow::setdata(){

    Archive a;
   ui->le_tab->setModel(a.Afficher());

}
void MainWindow::on_bouton_supp_clicked() {
    QString idStr = ui->le_id_supp->text(); // Get the text from le_id_supp

    bool ok; // Used to check if conversion to int was successful
    int id = idStr.toInt(&ok);

    if (ok) {
        Archive archive; // Create an instance of your Archive class
        if (archive.supprimer(id)) {
            // The record was deleted successfully
            QMessageBox::information(this, tr("Success"), tr("The record was deleted successfully."), QMessageBox::Ok);
            // You can add more handling code here if needed
        } else {
            // There was an error during the deletion
            QMessageBox::warning(this, tr("Error"), tr("An error occurred while deleting the record."), QMessageBox::Ok);
            // You can add more handling code here if needed
        }
    } else {
        // The entered ID is not a valid integer
        QMessageBox::warning(this, tr("Invalid ID"), tr("Please enter a valid integer ID."), QMessageBox::Ok);
        // You can add more handling code here if needed
    }

    setdata();

}




void MainWindow::on_pushButton_3_clicked()
{
    int id = ui->e_idE->text().toInt(); // Retrieve the ID from the QLineEdit

       if (id != 0) { // Check if a valid ID is entered

       QString nom = ui->e_nomE->text();


       QDateTime dateTime = ui->e_DateE->dateTime(); // Retrieve selected date and time

       QString type = ui->e_typeE->text();
       QString version = ui->e_versionE->text();

       QDate convertedDate = dateTime.date(); // Get the date part

       qDebug() << "Date String: " << dateTime;
       qDebug() << "Converted Date: " << convertedDate.toString("dd-MMM-yy");

           Archive A;
                 bool success = A.update(id, nom, convertedDate, type, version);

                 if (success) {
                     QMessageBox::information(this, "Success", "Update successful!");
                 } else {
                     QMessageBox::critical(this, "Error", "Update failed!");
                 }
             } else {
                 QMessageBox::warning(this, "Warning", "Please enter a valid ID.");
             }


       setdata();
}

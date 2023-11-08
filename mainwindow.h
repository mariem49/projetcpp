#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <archive.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    // Custom functions
    void setdata();
    void remplirListeArchive();


private slots:
    void on_pushButton_2_clicked();
    void on_bouton_supp_clicked();

    void on_pushButton_3_clicked();

private:

    Ui::MainWindow *ui;
    int selectedId;
    QString etatformulaire;
    int endusavec;
};
#endif // MAINWINDOW_H




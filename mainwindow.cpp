#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    ui->le_id->setValidator(new QIntValidator(0,999999,this));
    ui->tab_employe->setModel(e.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString mail=ui->le_mail->text();
    QString poste=ui->le_poste->text();
    employe e(id,nom,prenom,mail,poste);
    bool test=e.ajouter();
    if (test)
    {
        { QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectué\nClick Cancel to exit"), QMessageBox::Cancel);}
         ui->tab_employe->setModel(e.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\nClick Cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_supprimer_clicked()
{

    QString id_str = ui->le_id_sup->text();
    bool id_is_valid = false;
    int id = id_str.toInt(&id_is_valid);

    if (id_is_valid)
    {
        employe e1;
        e1.setid(id);

        bool test = e1.supprimer(e1.getid());

        if (test)
        {
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée.\nClick Cancel to exit"), QMessageBox::Cancel);
              ui->tab_employe->setModel(e.afficher());
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Échec de suppression.\nClick Cancel to exit"), QMessageBox::Cancel);
             ui->tab_employe->setModel(e.afficher());
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("ID non valide.\nClick Cancel to exit"), QMessageBox::Cancel);
    }
}

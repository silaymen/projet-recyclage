#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipement.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_equipement->setModel(E.afficher());//refresh
    ui->tab_equipement_2->setModel(E.afficher());//refresh
    ui->tab_equipement_5->setModel(E.afficher());//refresh


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{
    // Réinitialisez les étiquettes d'erreur à vide
    ui->lblErreurId->setText("");
    ui->lblErreurType->setText("");
    ui->lblErreurEtat->setText("");
    ui->lblErreurPrix->setText("");
    ui->lblErreurNiveauremplissage->setText("");
    ui->lblErreurDate_acquisation->setText("");  // Correction du nom de la variable
    ui->lblErreuridZ->setText("");  // Correction du nom de la variable

    // Récupérez les valeurs d'entrée
    QString id_equipement = ui->le_idequipement->text();
    QString type = ui->type->currentText();
    QString etat = ui->etat->currentText();
    int prix = ui->prix->text().toInt();
    float niveau_remplissage = ui->niveauremplissage->text().toFloat();
    QDate date_acquisition = ui->date->date();  // Correction du nom de la variable

    QString idZ = ui->idZone->text();

    // Validez les champs d'entrée
    bool isValid = true;

    if (id_equipement.isEmpty()) {
        ui->lblErreurId->setText("<font color='red'>ID Equipement ne peut pas être vide!!!!</font>");
        isValid = false;
    }

    // Validation pour le titre (exemplaire, assurez-vous qu'il n'est pas vide)
    if (type.isEmpty()) {
        ui->lblErreurType->setText("<font color='red'>Choisir un Type!!!</font>");
        isValid = false;
    }

    if (etat.isEmpty()) {
        ui->lblErreurEtat->setText("<font color='red'>Choisir un etat!!!</font>");
        isValid = false;
    }
    if (prix < 0) {
        ui->lblErreurPrix->setText("<font color='red'>Prix doit être positif !!!</font>");
        isValid = false;
    }
    if (niveau_remplissage < 0) {
        ui->lblErreurNiveauremplissage->setText("<font color='red'>Niveau remplissage doit être positif!!!</font>");
        isValid = false;
    }

    // Ajouter une vérification de l'existence de l'ID dans la base de données
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id_equipement from equipement  WHERE id_equipement = :id_equipement");
    checkQuery.bindValue(":id_equipement", id_equipement);
    if (checkQuery.exec() && checkQuery.next()) {
        ui->lblErreurId->setText("<font color='red'>ID Equipement existe déjà!!!!</font>");
        isValid = false;
    }

    if (isValid) {
        // Si l'entrée est valide et que l'ID n'existe pas, procédez à l'ajout de l'activité
        Equipement E(id_equipement, type, etat, prix, niveau_remplissage, date_acquisition, idZ);  // Correction de la création de l'objet Equipement

        QSqlQuery query;
        bool test = E.ajouter();
        if (test) {
            ui->tab_equipement->setModel(E.afficher());  // Refresh
            ui->tab_equipement_2->setModel(E.afficher());  // Refresh
            ui->tab_equipement_5->setModel(E.afficher());  // Refresh
ui->comboSupp->setModel(E.afficher());
ui->ComboModif->setModel(E.afficher());

            QMessageBox::information(nullptr, QObject::tr("Ajout Equipement"),
                QObject::tr("Equipement ajouté avec succès.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Ajout Equipement"),
                QObject::tr("Erreur lors de l'ajout de l'Equipement.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
    } else {
        // Gérez l'erreur d'entrée invalide ou d'ID existant
    }
}

void MainWindow::on_pb_afficher_clicked()
{
    ui->tab_equipement->setModel(E.afficher());//refresh
    ui->tab_equipement_2->setModel(E.afficher());//refresh
    ui->tab_equipement_5->setModel(E.afficher());//refresh


}

void MainWindow::on_pb_supprimer_2_clicked()
{
    QString id_equipement=ui->comboSupp->currentText();

    bool test=E.supprimer(id_equipement);
    if(test)
    {
        ui->tab_equipement->setModel(E.afficher());//refresh
        ui->tab_equipement_2->setModel(E.afficher());//refresh
        ui->tab_equipement_5->setModel(E.afficher());//refresh

        ui->comboSupp->setModel(E.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer Equipement"),
                    QObject::tr("Equipement supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


        ui->comboSupp->setModel(E.afficher());
        ui->ComboModif->setModel(E.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Equipement"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_modifier_2_clicked()
{
    // Récupérez les valeurs d'entrée
    QString id_equipement = ui->ComboModif->currentText();
    QString type = ui->type2->currentText();
    QString etat = ui->etat2->currentText();
    int prix = ui->prix2->text().toInt();
    float niveau_remplissage = ui->niveauremplissage2->text().toFloat();
    QDate date_acquisation = ui->date2->date();
    QString idZ = ui->idZone2->text();

    // Créez un objet Equipement en utilisant le constructeur
    Equipement E(id_equipement, type, etat, prix, niveau_remplissage, date_acquisation, idZ);

    QSqlQuery query;

    bool test = E.modifier();
    if (test)
    {
        ui->tab_equipement->setModel(E.afficher());  // Refresh
        ui->tab_equipement_2->setModel(E.afficher());  // Refresh
        ui->tab_equipement_5->setModel(E.afficher());  // Refresh

        QMessageBox::information(nullptr, QObject::tr("Modifier Equipement"),
            QObject::tr("Equipement modifié avec succès.\n"
                        "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);

        // Mettez à jour les modèles pour les combobox
        ui->comboSupp->setModel(E.afficher());
        ui->ComboModif->setModel(E.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier Equipement"),
            QObject::tr("Erreur lors de la modification de l'Equipement.\n"
                        "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }

    ui->ComboModif->clear();  // Effacez le contenu du combobox
}

void MainWindow::on_pb_afficher_3_clicked()
{
    ui->tab_equipement->setModel(E.afficher());//refresh
    ui->tab_equipement_2->setModel(E.afficher());//refresh
    ui->tab_equipement_5->setModel(E.afficher());//refresh


}

void MainWindow::on_pb_afficher_4_clicked()
{
    ui->tab_equipement->setModel(E.afficher());//refresh
    ui->tab_equipement_2->setModel(E.afficher());//refresh
    ui->tab_equipement_5->setModel(E.afficher());//refresh
}

void MainWindow::on_valider1_2_clicked()
{
    {
        QString id_equipement=ui->ComboModif->currentText();
                  QSqlQuery query;
                  query.prepare("select * from equipement where id_equipement='"+id_equipement+"'");
                  if (query.exec())
                  {
                   while (query.next())
                   {


                       ui->type2->setCurrentText(query.value(1).toString());
                       ui->etat2->setCurrentText(query.value(2).toString());
                       ui->prix2->setText(query.value(3).toString());
                       ui->niveauremplissage2->setText(query.value(4).toString());

                       ui->date2->setDate(query.value(5).toDate());
                       ui->idZone2->setText(query.value(6).toString());






                   }
                  }


}}

void MainWindow::on_reset_clicked()
{
    ui->ComboModif->clear();

        ui->type2->clear();
        ui->etat2->clear();

        ui->prix2->clear();
        ui->niveauremplissage2->clear();
        ui->date2->clear();
        ui->idZone2->clear();
}

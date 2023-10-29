#include "equipement.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QtDebug>
#include <QObject>
#include<QDate>
#include<QMessageBox>
#include <QSqlError>
#include <QDebug>
Equipement::Equipement()
{

}

Equipement::Equipement(QString id_equipement,QString type,QString etat,int prix,int niveau_remplissage,QDate date_acquisation,QString idZ)
{this->id_equipement=id_equipement;
    this->type = type;
    this->etat = etat;
    this->prix = prix;
    this->niveau_remplissage = niveau_remplissage;
this->date_acquisation=date_acquisation;
    this->idZ=idZ;
}

  QString Equipement::getID(){return id_equipement;}
  QString Equipement::getType(){return type;}
  QString Equipement::getEtat(){return etat;}
  int Equipement::getPrix(){return prix;}
  int Equipement::getNiveau(){return niveau_remplissage;}
  QDate Equipement::getDate(){return date_acquisation;}
  QString Equipement::getidZ(){return  idZ;}

  void Equipement::setID(QString id_equipement){this->id_equipement=id_equipement;}
  void Equipement::setType(QString type){this->type=type;}
  void Equipement::setEtat(QString etat){this->etat=etat;}
  void Equipement::setPrix(int prix){this->prix=prix;}
  void Equipement::setNiveau(int niveau_remplissage ){this->niveau_remplissage=niveau_remplissage;}
  void Equipement::setDate(QDate date_acquisation){this->date_acquisation=date_acquisation;}
  void Equipement::setidZ(QString idZ) {this->idZ=idZ;}

bool Equipement::ajouter()
{

    QSqlQuery query;

    query.prepare("INSERT INTO Equipement (id_equipement,type,etat,prix,niveau_remplissage,date_acquisation,idZ)"
                  "values(:id_equipement,:type,:etat,:prix,:niveau_remplissage,:date_acquisation,:idZ)");
    query.bindValue(":id_equipement",id_equipement);
        query.bindValue(":type",type);
         query.bindValue(":etat",etat);
         query.bindValue(":prix",prix);
         query.bindValue(":niveau_remplissage",niveau_remplissage);
query.bindValue(":date_acquisation",date_acquisation);
query.bindValue(":idZ",idZ);

          return query.exec();

   };



QSqlQueryModel * Equipement::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Equipement");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_equipement"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("etat"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("niveau_remplissage"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_acquisation"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("idZ"));


    return model;
}

bool Equipement::supprimer(QString id_equipement)
{
    QSqlQuery query;
         query.prepare("Delete from Equipement where id_equipement=:id_equipement");
         query.bindValue(":id_equipement",id_equipement);
         return query.exec();
}



bool Equipement::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE Equipement SET id_equipement = :id_equipement, type = :type, etat = :etat, prix = :prix, niveau_remplissage = :niveau_remplissage, date_acquisation = :date_acquisation, idZ = :idZ WHERE id_equipement = :id_equipement");

    query.bindValue(":id_equipement", id_equipement);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":prix", prix);
    query.bindValue(":niveau_remplissage", niveau_remplissage);
    query.bindValue(":date_acquisation", date_acquisation);
    query.bindValue(":idZ", idZ);

    return query.exec();
}

bool Equipement::checkIfIdExists(QString id)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM Equipement WHERE id_equipement = :id_equipement");
    query.bindValue(":id_equipement", id_equipement);

    if (query.exec() && query.next()) {
        // The ID exists in the database
        return true;
    } else {
        // The ID does not exist in the database
        return false;
    }
}

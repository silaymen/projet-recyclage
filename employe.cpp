#include "employe.h"
#include <QDebug>
#include <QObject>
employe::employe(int id,QString nom,QString prenom,QString poste,QString mail)
{

this->id=id;
this->nom=nom;
this->prenom=prenom;
this->poste=poste;
this->mail=mail;
}
bool employe::ajouter()
{

    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("insert into employe (id,nom,prenom,mail,poste)" "values(:id, :nom, :prenom, :mail, :poste)");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":mail",mail);
    query.bindValue(":poste",poste);
    return query.exec();
}

QSqlQueryModel * employe::afficher()
{

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from EMPLOYE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("poste"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("mail"));


    return model;
}

bool employe::supprimer(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("delete from EMPLOYE where ID=:id" );
    query.bindValue(":id",res);

 return query.exec();
}

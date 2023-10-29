#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class Equipement
{
public:
    Equipement();

    Equipement(QString,QString,QString,int,int,QDate,QString);
    QString getID();
    QString getType();
    QString getEtat();
    int getPrix();
    int getNiveau();
    QDate getDate();
    QString getidZ();

    void setID(QString);
    void setType(QString);
    void setEtat(QString );
    void setPrix(int);
    void setNiveau(int );
    void setDate(QDate);
    void setidZ(QString);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier();

    bool checkIfIdExists(QString);

private:
    QString id_equipement,type,etat,idZ;
    int prix;
    int niveau_remplissage;
    QDate date_acquisation;


};

#endif // EQUIPEMENT_H

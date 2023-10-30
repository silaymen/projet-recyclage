#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QSqlQuery>
#include<QSqlQueryModel>
class employe
{
    QString nom,prenom,mail,poste;
    int id;
public:
    employe(){}
    employe(int,QString,QString,QString,QString);
    //
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    int getid(){return id;}
    QString getposte(){return poste;}
    QString getmail(){return mail;}
    //
    void setnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}    
    void setposte(QString e){poste=e;}
    void setmail(QString m){mail=m;}

    void setid(int id){this->id=id;}
    //
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
};

#endif // EMPLOYE_H

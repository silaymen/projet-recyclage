#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_Projet2A");
db.setUserName("louai");//inserer nom de l'utilisateur
db.setPassword("louay");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}

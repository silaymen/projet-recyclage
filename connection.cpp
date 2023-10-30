#include "connection.h"
#include <QDebug>
Connection::Connection()
{

}

bool Connection::createconnect()

{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Projet");
    db.setUserName("aymenn");
    db.setPassword("aymenn");

    if (db.open())
    {
        test = true;
    }


    return test;
}
void Connection::closeConnection(){db.close();}

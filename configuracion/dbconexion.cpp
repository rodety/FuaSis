#include "dbconexion.h"

dbconexion* dbconexion::instance = 0;
dbconexion::dbconexion()
{
    qDebug() <<openconexion();

}

int dbconexion::openconexion()
{
    if(!QSqlDatabase::isDriverAvailable("QSQLITE")){
        QMessageBox msgBox;
        msgBox.setText("Error Driver QSQLITE no esta disponible");
        msgBox.exec();

        return -1;
    }
    QSqlDatabase bd = QSqlDatabase::addDatabase(("QSQLITE"));
    bd.setDatabaseName("dbdata.db");
    if(!bd.open()){
        QMessageBox msgBox;
        msgBox.setText(bd.lastError().text());
        msgBox.exec();

        return -2;
    }
    return -3;

}

dbconexion *dbconexion::getInstance()
{
    if (instance == 0)
       {
           instance = new dbconexion();
       }

       return instance;
}

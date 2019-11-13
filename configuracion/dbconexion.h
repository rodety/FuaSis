#ifndef DBCONEXION_H
#define DBCONEXION_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QMessageBox>
class dbconexion
{
private:
    static dbconexion* instance;
    dbconexion();
    int openconexion();
public:
    static dbconexion* getInstance();

};

#endif // DBCONEXION_H

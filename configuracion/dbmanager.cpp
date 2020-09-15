#include "dbmanager.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

dbmanager::dbmanager()
{

}

int dbmanager::createDB()
{
    QMessageBox msgBox;
    QSqlQuery q;
    if(!q.exec("CREATE TABLE IF NOT EXISTS paciente"
               " (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               " COD_RENAES VARCHAR(4),"
               " EESS VARCHAR(255),"
               " DISA VARCHAR(3),"
               " T_AFIL CHAR(1),"
               " NRO_AFIL INTEGER,"
               " AFIL_DNI VARCHAR(10),"
               " F_AFIL VARCHAR(10),"
               " APEL_NOM VARCHAR(255),"
               " SEX CHAR(1),"
               " F_NACIMIENTO VARCHAR(10),"
               " EDAD VARCHAR(3),"
               " F_BAJA VARCHAR(10),"
               " NRO_HISTORIA VARCHAR(10),"
               " ETNIA VARCHAR(2))")){

        msgBox.setText(q.lastError().text());
        msgBox.exec();

        return -3;
    }

    if(!q.exec("CREATE TABLE IF NOT EXISTS atencion"
               " (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               " NRO_FORMATO VARCHAR(15),"
               " AFIL_DNI INTEGER,"
               " FEC_ATENCION VARCHAR(10),"
               " EESS VARCHAR(255),"
               " SERVICIO VARCHAR(3),"
               " CONTRATO VARCHAR(15),"
               " TPROFESIONAL VARCHAR(50),"
               " PROFESIONAL VARCHAR(255),"
               " TARIFA VARCHAR(3),"
               " DIAGNOSTICO VARCHAR(255),"
               " TIPO_ATENCION VARCHAR(15),"
               " FECHA_REGISTRO VARCHAR(10),"
               " LUGAR_ATENCION VARCHAR(10),"
               " CONVENIO VARCHAR(15),"
               " HIS_CLI VARCHAR(10),"
               " EESS_REFERENCIA VARCHAR(10),"
               " PERIODO VARCHAR(7),"
               " CON_MATERNA VARCHAR(15),"
               " COMPONENTE VARCHAR(20),"
               " TIPO_PAGO VARCHAR(15),"
               " EDAD_GESTACIONAL VARCHAR(10),"
               " DESTINO VARCHAR(25),"
               " FEC_PARTO VARCHAR(10),"
               " FEC_PROB_PARTO VARCHAR(10),"
               " FOREIGN KEY(AFIL_DNI) REFERENCES paciente(AFIL_DNI))")){

        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -4;
    }


    if(!q.exec("CREATE TABLE IF NOT EXISTS predeterminado"
               " (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               " IPRESS VARCHAR(10),"
               " NOMBRE_IPRESS VARCHAR(40),"
               " PERSONAL_ATIENDE CHAR(1),"
               " LUGAR_ATENCION CHAR(1),"
               " ATENCION CHAR(1))")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }

    if(!q.exec("CREATE TABLE IF NOT EXISTS medida"
               " (ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               " FACTOR_AJUSTE VARCHAR(20),"
               " COD_EESS VARCHAR(10),"
               " NOM_EESS VARCHAR(10),"
               " IPRESS VARCHAR(10),"
               " ITINERANTE VARCHAR(10),"
               " OFERTA VARCHAR(10),"
               " INTRAMURAL VARCHAR(10),"
               " EXTRAMURAL VARCHAR(10),"
               " AMBULATORIA VARCHAR(10),"
               " REFERENCIA VARCHAR(10),"
               " EMERGENCIA VARCHAR(10),"
               " COD_RENAES VARCHAR(10),"
               " NOMBRE_IPRESS VARCHAR(10),"
               " HOJA_REFERENCIA VARCHAR(10),"
               " TDI VARCHAR(10),"
               " DOCUMENTO_IDENTIDAD VARCHAR(10),"
               " DIRESA VARCHAR(10),"
               " NUMERO VARCHAR(10),"
               " INSTITUCION VARCHAR(10),"
               " COD_SEGURO VARCHAR(10),"
               " APELL_PATERNO VARCHAR(10),"
               " APELL_MATERNO VARCHAR(10),"
               " NOMBRES VARCHAR(10),"
               " OTROS_NOMBRES VARCHAR(10),"
               " SEX_M VARCHAR(10),"
               " SEX_F VARCHAR(10),"
               " GESTANTE VARCHAR(10),"
               " PUERPERA VARCHAR(10),"
               " FEC_PARTO VARCHAR(10),"
               " FEC_NACIMIENTO VARCHAR(10),"
               " FEC_FALLECIMIENTO VARCHAR(10),"
               " NUM_HISTORIA VARCHAR(10),"
               " ETNIA VARCHAR(10),"
               " DNI_CNV_AFIL_RN VARCHAR(10),"
               " FEC_ATENCION VARCHAR(10),"
               " COD_PRES VARCHAR(10),"
               " ATE_DIREC VARCHAR(10),"
               " ASEGURADO VARCHAR(10),"
               " COD_RENAES_CONTRAREF VARCHAR(10),"
               " NOMBRE_IPRESS_CONTRAREF VARCHAR(10),"
               " DESCRIPCION1 VARCHAR(10),"
               " DESCRIPCION2 VARCHAR(10),"
               " DESCRIPCION3 VARCHAR(10),"
               " DESCRIPCION4 VARCHAR(10),"
               " DESCRIPCION5 VARCHAR(10),"
               " PI1 VARCHAR(10),"
               " PI2 VARCHAR(10),"
               " PI3 VARCHAR(10),"
               " PI4 VARCHAR(10),"
               " PI5 VARCHAR(10),"
               " DI1 VARCHAR(10),"
               " DI2 VARCHAR(10),"
               " DI3 VARCHAR(10),"
               " DI4 VARCHAR(10),"
               " DI5 VARCHAR(10),"
               " RI1 VARCHAR(10),"
               " RI2 VARCHAR(10),"
               " RI3 VARCHAR(10),"
               " RI4 VARCHAR(10),"
               " RI5 VARCHAR(10),"
               " DE1 VARCHAR(10),"
               " DE2 VARCHAR(10),"
               " DE3 VARCHAR(10),"
               " DE4 VARCHAR(10),"
               " DE5 VARCHAR(10),"
               " RE1 VARCHAR(10),"
               " RE2 VARCHAR(10),"
               " RE3 VARCHAR(10),"
               " RE4 VARCHAR(10),"
               " RE5 VARCHAR(10),"
               " DNI_RESP VARCHAR(10),"
               " NOMBRE_RESP VARCHAR(10),"
               " COLEGIATURA_RESP VARCHAR(10),"
               " CODIGO_RESP VARCHAR(10),"
               " ESPECIALIDAD_RESP VARCHAR(10),"
               " RNE_RESP VARCHAR(10),"
               " EGRESADO_RESP VARCHAR(10))")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("INSERT OR IGNORE INTO medida("
               "FACTOR_AJUSTE,"
               "COD_EESS,"
               "NOM_EESS,"
               "IPRESS,"
               "ITINERANTE,"
               "OFERTA,"
               "INTRAMURAL,"
               "EXTRAMURAL,"
               "AMBULATORIA,"
               "REFERENCIA,"
               "EMERGENCIA,"
               "COD_RENAES,"
               "NOMBRE_IPRESS,"
               "HOJA_REFERENCIA,"
               "TDI,"
               "DOCUMENTO_IDENTIDAD,"
               "DIRESA,"
               "NUMERO,"
               "INSTITUCION,"
               "COD_SEGURO,"
               "APELL_PATERNO,"
               "APELL_MATERNO,"
               "NOMBRES,"
               "OTROS_NOMBRES,"
               "SEX_M,"
               "SEX_F,"
               "GESTANTE,"
               "PUERPERA,"
               "FEC_PARTO,"
               "FEC_NACIMIENTO,"
               "FEC_FALLECIMIENTO,"
               "NUM_HISTORIA,"
               "ETNIA,"
               "DNI_CNV_AFIL_RN,"
               "FEC_ATENCION,"
               "COD_PRES,"
               "ATE_DIREC,"
               "ASEGURADO,"
               "COD_RENAES_CONTRAREF,"
               "NOMBRE_IPRESS_CONTRAREF,"
               "DESCRIPCION1,"
               "DESCRIPCION2,"
               "DESCRIPCION3,"
               "DESCRIPCION4,"
               "DESCRIPCION5,"
               "PI1,"
               "PI2,"
               "PI3,"
               "PI4,"
               "PI5,"
               "DI1,"
               "DI2,"
               "DI3,"
               "DI4,"
               "DI5,"
               "RI1,"
               "RI2,"
               "RI3,"
               "RI4,"
               "RI5,"
               "DE1,"
               "DE2,"
               "DE3,"
               "DE4,"
               "DE5,"
               "RE1,"
               "RE2,"
               "RE3,"
               "RE4,"
               "RE5,"
               "DNI_RESP,"
               "NOMBRE_RESP,"
               "COLEGIATURA_RESP,"
               "CODIGO_RESP,"
               "ESPECIALIDAD_RESP,"
               "RNE_RESP,"
              "EGRESADO_RESP ) VALUES('"
              "0.0265467-0.0265467','"
              "143-145','"
              "355-145','"
              "114-183','"
              "114-198','"
              "114-213','"
              "298-183','"
              "298-198','"
              "385-183','"
              "385-198','"
              "385-213','"
              "406-210','"
              "492-210','"
              "683-210','"
              "50-264','"
              "83-264','"
              "210-264','"
              "254-264','"
              "470-251','"
              "470-264','"
               "44-296','"
               "400-296','"
               "44-322','"
               "400-322','"
               "89-347','"
               "89-356','"
               "89-380','"
               "89-392','"
               "174-353','"
               "174-373','"
               "174-390','"
               "370-355','"
               "666-356','"
               "666-369','"
               "44-444','"
               "355-444','"
               "107-506','"
               "417-972','"
               "44-620','"
               "298-620','"
               "1-1','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30','"
               "30-30')")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -100;
    }
    if(!q.exec("CREATE TABLE IF NOT EXISTS cie"
               " (ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               " COD_CAT VARCHAR(4),"
               " DESC_ENF VARCHAR(100))")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -11;
    }
    if(!q.exec("CREATE TABLE IF NOT EXISTS profesional"
               " (ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               " DNI VARCHAR(8),"
               " NOMBRE VARCHAR(100),"
               " COLEGIATURA VARCHAR(8),"
               " CODIGO VARCHAR(1),"
               " ESPECIALIDAD VARCHAR(1),"
               " RNE VARCHAR(8),"
               " EGRESADO VARCHAR(4))")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -12;
    }

    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_APEL_NOM ON paciente (APEL_NOM);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -6;
    }
    if(!q.exec("CREATE UNIQUE INDEX IF NOT EXISTS IDX_AFIL_DNI ON paciente (AFIL_DNI);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -7;

    }
    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_NRO_HISTORIA ON paciente (NRO_HISTORIA);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -8;
        //NRO_HISTORIA
    }

    if(!q.exec("CREATE INDEX IF NOT EXISTS IDXA_AFIL_DNI ON atencion (AFIL_DNI);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -9;
    }
    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_DESC_ENF ON cie (DESC_ENF);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -12;
    }
    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_COD_CAT ON cie (COD_CAT);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -13;
    }
    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_DNI ON profesional (DNI);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -14;
    }
    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_NOMBRE ON profesional (NOMBRE);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -15;
    }
    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_COLEGIATURA ON profesional (COLEGIATURA);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -16;
    }

    return -10;

}

int dbmanager::updateDB()
{
    QMessageBox msgBox;
    QSqlQuery q;




    if(!q.exec("ALTER TABLE medida ADD COD_RENAES_CONTRAREF VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }

    if(!q.exec("ALTER TABLE medida ADD NOMBRE_IPRESS_CONTRAREF VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }

    if(!q.exec("ALTER TABLE medida ADD DESCRIPCION1 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DESCRIPCION2 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DESCRIPCION3 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DESCRIPCION4 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DESCRIPCION5 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD PI1 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD PI2 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD PI3 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD PI4 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD PI5 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DI1 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DI2 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DI3 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DI4 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DI5 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD RI1 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD RI2 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD RI3 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD RI4 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD RI5 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DE1 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DE2 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DE3 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DE4 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD DE5 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD RE1 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD RE2 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD RE3 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD RE4 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD RE5 VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }

    if(!q.exec("ALTER TABLE medida ADD DNI_RESP VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD NOMBRE_RESP VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD COLEGIATURA_RESP VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD CODIGO_RESP VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD ESPECIALIDAD_RESP VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }
    if(!q.exec("ALTER TABLE medida ADD RNE_RESP VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }

    if(!q.exec("ALTER TABLE medida ADD EGRESADO_RESP VARCHAR(10)")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -5;
    }

    if(!q.exec("UPDATE medida SET "
               "FACTOR_AJUSTE='0.0265467-0.0265467', "
               "COD_EESS='143-145', "
               "NOM_EESS='355-145', "
               "IPRESS='114-183', "
               "ITINERANTE='114-198', "
               "OFERTA='114-213', "
               "INTRAMURAL='298-183', "
               "EXTRAMURAL='298-198', "
               "AMBULATORIA='385-183', "
               "REFERENCIA='385-198', "
               "EMERGENCIA='385-213', "
               "COD_RENAES='406-210', "
               "NOMBRE_IPRESS='492-210', "
               "HOJA_REFERENCIA='683-210', "
               "TDI='50-264', "
               "DOCUMENTO_IDENTIDAD='83-264', "
               "DIRESA='210-264', "
               "NUMERO='254-264', "
               "INSTITUCION='470-251', "
               "COD_SEGURO='470-264', "
               "APELL_PATERNO='44-296', "
               "APELL_MATERNO='400-296', "
               "NOMBRES='44-322', "
               "OTROS_NOMBRES='400-322', "
               "SEX_M='89-347', "
               "SEX_F='89-356', "
               "GESTANTE='89-380', "
               "PUERPERA='89-392', "
               "FEC_PARTO='174-353', "
               "FEC_NACIMIENTO='174-373', "
               "FEC_FALLECIMIENTO='174-390', "
               "NUM_HISTORIA='370-355', "
               "ETNIA='666-356', "
               "DNI_CNV_AFIL_RN='666-369', "
               "FEC_ATENCION='44-444', "
               "COD_PRES='355-444', "
               "ATE_DIREC='107-506', "
               "ASEGURADO='417-972', "
               "COD_RENAES_CONTRAREF='44-620', "
               "NOMBRE_IPRESS_CONTRAREF='298-620', "
               "DESCRIPCION1='30-30', "
               "DESCRIPCION2='30-30', "
               "DESCRIPCION3='30-30', "
               "DESCRIPCION4='30-30', "
               "DESCRIPCION5='30-30', "
               "PI1='30-30', "
               "PI2='30-30', "
               "PI3='30-30', "
               "PI4='30-30', "
               "PI5='30-30', "
               "DI1='30-30', "
               "DI2='30-30', "
               "DI3='30-30', "
               "DI4='30-30', "
               "DI5='30-30', "
               "RI1='30-30', "
               "RI2='30-30', "
               "RI3='30-30', "
               "RI4='30-30', "
               "RI5='30-30', "
               "DE1='30-30', "
               "DE2='30-30', "
               "DE3='30-30', "
               "DE4='30-30', "
               "DE5='30-30', "
               "RE1='30-30', "
               "RE2='30-30', "
               "RE3='30-30', "
               "RE4='30-30', "
               "RE5='30-30', "
               "DNI_RESP='30-30', "
               "NOMBRE_RESP='30-30', "
               "COLEGIATURA_RESP='30-30', "
               "CODIGO_RESP='30-30', "
               "ESPECIALIDAD_RESP='30-30', "
               "RNE_RESP='30-30', "
              "EGRESADO_RESP='30-30'WHERE id = 1")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -100;
    }
    if(!q.exec("CREATE TABLE IF NOT EXISTS cie"
               " (ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               " COD_CAT VARCHAR(4),"
               " DESC_ENF VARCHAR(100))")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -11;
    }
    if(!q.exec("CREATE TABLE IF NOT EXISTS profesional"
               " (ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               " DNI VARCHAR(8),"
               " NOMBRE VARCHAR(100),"
               " COLEGIATURA VARCHAR(8),"
               " CODIGO VARCHAR(1),"
               " ESPECIALIDAD VARCHAR(1),"
               " RNE VARCHAR(8),"
               " EGRESADO VARCHAR(4))")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -12;
    }


    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_DESC_ENF ON cie (DESC_ENF);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -120;
    }
    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_COD_CAT ON cie (COD_CAT);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -13;
    }
    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_DNI ON profesional (DNI);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -14;
    }
    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_NOMBRE ON profesional (NOMBRE);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -15;
    }
    if(!q.exec("CREATE INDEX IF NOT EXISTS IDX_COLEGIATURA ON profesional (COLEGIATURA);")){
        msgBox.setText(q.lastError().text());
        msgBox.exec();
        return -16;
    }

    return -10;



}

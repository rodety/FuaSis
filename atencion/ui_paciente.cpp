#include "ui_paciente.h"
#include "ui_ui_paciente.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QMessageBox>

ui_paciente::ui_paciente(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_paciente)
{
    ui->setupUi(this);
}

ui_paciente::~ui_paciente()
{
    delete ui;
}

void ui_paciente::on_pushButton_guardar_clicked()
{
    QSqlQuery q;
    QString query;
    QString SEX,F_AFIL,F_NACIMIENTO,F_BAJA;
    if(ui->radioButton_sex_m->isChecked()){
        SEX="M";
    }
    if(ui->radioButton_sex_f->isChecked()){
        SEX="M";
    }

        F_AFIL=ui->dateEdit_f_afil->text();


        F_NACIMIENTO=ui->dateEdit_fec_nac->text();


        F_BAJA=ui->dateEdit_fec_baja->text();

    if(comportamiento== "N"){
        query = "INSERT OR IGNORE INTO paciente ("
                "COD_RENAES,"
                "EESS,"
                "DISA,"
                "T_AFIL,"
                "NRO_AFIL,"
                "AFIL_DNI,"
                "F_AFIL,"
                "APEL_NOM,"
                "SEX,"
                "F_NACIMIENTO,"
                "EDAD,"
                "F_BAJA,"
                "NRO_HISTORIA,"
                "ETNIA"
                ") VALUES('"+ui->lineEdit_cod_renaes->text()+"','"+
                ui->lineEdit_eess->text()+"','"+
                ui->lineEdit_disa->text()+"','"+
                ui->lineEdit_t_afil->text()+"','"+
                ui->lineEdit_nro_afil->text()+"','"+
                ui->lineEdit_afil_dni->text()+"','"+
                F_AFIL+"','"+
                ui->lineEdit_apel_paterno->text()+" "+ui->lineEdit_apel_materno->text()+" "+ui->lineEdit_nombres->text()+"','"+
                SEX+"','"+
                F_NACIMIENTO+"','"+
                ui->lineEdit_edad->text()+"','"+
                F_BAJA+"','"+
                ui->lineEdit_nro_his->text()+"','"+
                ui->lineEdit_etnia->text()+"')";
    }
    if(comportamiento== "E"){
        query = "UPDATE OR IGNORE paciente SET "
                "COD_RENAES ='"+ui->lineEdit_cod_renaes->text()+"',"+
                "EESS='"+ui->lineEdit_eess->text()+"',"+
                "DISA='"+ui->lineEdit_disa->text()+"',"+
                "T_AFIL='"+ui->lineEdit_t_afil->text()+"',"+
                "NRO_AFIL='"+ui->lineEdit_nro_afil->text()+"',"+
                "F_AFIL='"+F_AFIL+"',"+
                "APEL_NOM='"+ui->lineEdit_apel_paterno->text()+" "+ui->lineEdit_apel_materno->text()+" "+ui->lineEdit_nombres->text()+"',"+
                "SEX='"+SEX+"',"+
                "F_NACIMIENTO='"+F_NACIMIENTO+"',"+
                "EDAD='"+ui->lineEdit_edad->text()+"',"+
                "F_BAJA='"+F_BAJA+"',"+
                "NRO_HISTORIA='"+ui->lineEdit_nro_his->text()+"',"+
                "ETNIA='"+ui->lineEdit_etnia->text()+"'"+
                " WHERE AFIL_DNI = '"+ui->lineEdit_afil_dni->text()+"'";
    }


    if(!q.exec(query)){
        qDebug() <<q.lastError().text();
    }
    else{
        if(comportamiento=="N"){
            QMessageBox msgBox;
            msgBox.setText("Datos Guardados Correctamente");
            msgBox.exec();
        }
        if(comportamiento=="E"){
            QMessageBox msgBox;
            msgBox.setText("Datos Actualizados Correctamente");
            msgBox.exec();
        }
    }
    this->close();

}

void ui_paciente::on_pushButton_cancelar_clicked()
{
    this->close();
}

void ui_paciente::loadDefaultNew()
{
    comportamiento = "N";
    QSqlQuery query;
    query.prepare("SELECT * FROM predeterminado");
    //query.bindValue(0,numeroDocumento);
    QString ID,IPRESS,NOMBRE_IPRESS,PERSONAL_ATIENDE,LUGAR_ATENCION,ATENCION;
    if(query.exec())
    {
        if(query.size()!=0)
        {
            query.first();
            ID=query.value(0).toString();
            IPRESS=query.value(1).toString();
            NOMBRE_IPRESS=query.value(2).toString();
            PERSONAL_ATIENDE=query.value(3).toString();
            LUGAR_ATENCION=query.value(4).toString();
            ATENCION=query.value(5).toString();
        }
        //LLENANDO DATOS
        ui->lineEdit_cod_renaes->setText(IPRESS);
        ui->lineEdit_eess->setText(NOMBRE_IPRESS);
        ui->lineEdit_disa->setText("290");
        ui->lineEdit_t_afil->setText("R");
        ui->lineEdit_etnia->setText("54");



    }
}

void ui_paciente::loadDefaultEdit()
{
    comportamiento = "E";
    QSqlQuery query;
    query.prepare("SELECT * FROM paciente WHERE AFIL_DNI = ?");
    query.bindValue(0,DNI);
    QString ID,COD_RENAES,EESS,DISA,T_AFIL,NRO_AFIL,AFIL_DNI,F_AFIL,APEL_NOM,SEX,F_NACIMIENTO,EDAD,F_BAJA,NRO_HISTORIA,ETNIA;
    query.exec();
    {
        if(query.size()!=0)
        {
            query.first();
            ID=query.value(0).toString();
            COD_RENAES=query.value(1).toString();
            EESS=query.value(2).toString();
            DISA=query.value(3).toString();
            T_AFIL=query.value(4).toString();
            NRO_AFIL=query.value(5).toString();
            AFIL_DNI=query.value(6).toString();
            F_AFIL=query.value(7).toString();
            APEL_NOM=query.value(8).toString();
            SEX=query.value(9).toString();
            F_NACIMIENTO=query.value(10).toString();
            EDAD=query.value(11).toString();
            F_BAJA=query.value(12).toString();
            NRO_HISTORIA=query.value(13).toString();
            ETNIA=query.value(14).toString();
        }
        //LLENANDO DATOS
        ui->lineEdit_cod_renaes->setText(COD_RENAES);
        ui->lineEdit_eess->setText(EESS);


        ui->lineEdit_disa->setText(DISA);
        ui->lineEdit_t_afil->setText(T_AFIL);
        ui->lineEdit_nro_afil->setText(NRO_AFIL);
        ui->lineEdit_afil_dni->setText(DNI);
        QStringList s = F_AFIL.split("/");
        ui->dateEdit_f_afil->setDate(QDate(s.at(2).toInt(),s.at(1).toInt(),s.at(0).toInt()));

        QStringList Apellidos_nombres = APEL_NOM.split(' ');
        QStringList procesado;
        for(int i =0;i<Apellidos_nombres.size();i++){
            if(Apellidos_nombres.at(i).size() >2 && Apellidos_nombres.at(i) != "VDA"  )
                procesado.append(Apellidos_nombres.at(i));
        }


        if(procesado.size() > 0)
            ui->lineEdit_apel_paterno->setText(procesado.at(0));
        if(procesado.size() > 1)
            ui->lineEdit_apel_materno->setText(procesado.at(1));
        if(procesado.size() > 2)
            ui->lineEdit_nombres->setText(procesado.at(2));
        if(procesado.size() > 3)
            ui->lineEdit_nombres->setText(procesado.at(2)+" "+procesado.at(3));


        if(SEX == "M")
            ui->radioButton_sex_m->click();
        if(SEX == "F")
            ui->radioButton_sex_f->click();
        s = F_NACIMIENTO.split("/");
        ui->dateEdit_fec_nac->setDate(QDate(s.at(2).toInt(),s.at(1).toInt(),s.at(0).toInt()));


        ui->lineEdit_edad->setText(EDAD);
        s = F_NACIMIENTO.split("/");
        ui->dateEdit_fec_baja->setDate(QDate(s.at(2).toInt(),s.at(1).toInt(),s.at(0).toInt()));

        ui->lineEdit_nro_his->setText(NRO_HISTORIA);
        ui->lineEdit_etnia->setText(ETNIA);
        //
        //LLENANDO DATOS

    }
}

void ui_paciente::setDni(QString dni)
{

    this->DNI = dni;
}

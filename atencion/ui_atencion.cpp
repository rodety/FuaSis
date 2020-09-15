#include "ui_atencion.h"
#include "ui_ui_atencion.h"
#include "configuracion/dbconexion.h"
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <atencion/ui_paciente.h>
#include <QMessageBox>
#include "textedit.h"
#include <QCompleter>

ui_atencion::ui_atencion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_atencion),completer(0)
{
    ui->setupUi(this);
    loadDefaultData();

    //ui->tableView_result_search->setColumnWidth(0,300);
    //ui->tableView_result_search->setColumnWidth(1,900);

    connect (ui->tableView_result_search, SIGNAL (doubleClicked (const QModelIndex &)), this, SLOT (RowSelected (const QModelIndex &)));
    ui->tableView_result_search->setColumnWidth(0,300);
    ui->tableView_result_search->setColumnWidth(1,900);

    hash[3295] = "C.S. CARACOTO";
    hash[3302] = "P.S. 9 DE OCTUBRE";
    hash[3315] = "TAPARACHI";
    hash[3298] = "SUCHIS";
    hash[3304] = "COLLANA JULIACA";

    //DESHABILITANDO LINEEDIT
    ui->lineEdit_doc_identidad->setVisible(false);

    //DESHABILITANDO LINE EDIT REFERENCIA
    behaviorReferencia(false);
    createCodCie();
    createDescripcionCie();
    createResponsable();
    createDoc_indetidad();
    conexionSlot();
    activareDni_profe = true;
    activateNombre_profe = true;
    activateNro_colegiatura = true;

    activatedCie1 = true;
    activatedCie2 = true;
    activatedCie3 = true;
    activatedCie4 = true;
    activatedCie5 = true;

    activatedText1 = true;
    activatedText2 = true;
    activatedText3 = true;
    activatedText4 = true;
    activatedText5 = true;
}

ui_atencion::~ui_atencion()
{
    delete ui;
}


void ui_atencion::on_pushButton_guardar_eess_clicked()
{
    dbconexion* s = dbconexion::getInstance();
    QSqlQuery q;
    QString query;
    QString personal_atiente = "0", lugar_atencion ="0", atencion = "0";
    if(ui->radioButton_ipress->isChecked())
        personal_atiente = "1";
    if(ui->radioButton_itinerante->isChecked())
        personal_atiente = "2";
    if(ui->radioButton_oferta->isChecked())
        personal_atiente = "3";
    //SEGUNDA PARTE
    if(ui->radioButton_intramural->isChecked())
        lugar_atencion = "1";
    if(ui->radioButton_extramural->isChecked())
        lugar_atencion = "2";
    //TERCERA PARTE
    if(ui->radioButton_ambulatoria->isChecked())
        atencion = "1";
    if(ui->radioButton_referencia->isChecked())
        atencion = "2";
    if(ui->radioButton_emergencia->isChecked())
        atencion = "3";


    query = "INSERT OR REPLACE INTO predeterminado"
               " (id,"
               " IPRESS,"
               " NOMBRE_IPRESS,"
               " PERSONAL_ATIENDE,"
               " LUGAR_ATENCION,"
               " ATENCION) VALUES('1','"+
            ui->lineEdit_cod_eess->text()+"','"+
            ui->lineEdit_nom_eess->text()+"','"+
            personal_atiente+"','"+
            lugar_atencion+"','"+
            atencion+"')";            

    if(!q.exec(query)){
        qDebug() <<q.lastError().text();

    }


}

void ui_atencion::loadDefaultData()
{
    dbconexion* s = dbconexion::getInstance();
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
        ui->lineEdit_cod_eess->setText(IPRESS);
        ui->lineEdit_nom_eess->setText(NOMBRE_IPRESS);

        if(PERSONAL_ATIENDE == "1")
            ui->radioButton_ipress->setChecked(true);
        if(PERSONAL_ATIENDE == "2")
            ui->radioButton_itinerante->setChecked(true);
        if(PERSONAL_ATIENDE == "3")
            ui->radioButton_oferta->setChecked(true);
        //SEGUNDA PARTE
        if(LUGAR_ATENCION=="1")
            ui->radioButton_intramural->setChecked(true);
        if(LUGAR_ATENCION=="2")
            ui->radioButton_extramural->setChecked(true);
        //TERCERA PARTE
        if(ATENCION=="1")
            ui->radioButton_ambulatoria->setChecked(true);
        if(ATENCION=="2")
            ui->radioButton_referencia->setChecked(true);
        if(ATENCION=="3")
            ui->radioButton_emergencia->setChecked(true);

    }
    ui->dateEdit_fec_atencion->setDate(QDate::currentDate());






}

QSqlQueryModel *ui_atencion::buscarPaciente(QString _item)
{

    QSqlQueryModel *model = new QSqlQueryModel;
    QString query;

    //query = "SELECT ID as id, APEL_NOM as 'Apellidos y Nombres' FROM paciente WHERE AFIL_DNI='"+_item+"' OR APEL_NOM REGEXP '"+_item+"'";
    query= "SELECT AFIL_DNI as 'DNI', APEL_NOM as 'Apellidos y Nombres' FROM paciente WHERE APEL_NOM LIKE '%"+_item+"%' OR AFIL_DNI = '"+_item+"'";

    model->setQuery(query);
    return model;

}

QSqlQueryModel *ui_atencion::buscarAtenciones(QString _item)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query;

    //query = "SELECT ID as id, APEL_NOM as 'Apellidos y Nombres' FROM paciente WHERE AFIL_DNI='"+_item+"' OR APEL_NOM REGEXP '"+_item+"'";
    query= "SELECT * FROM atencion WHERE AFIL_DNI ='"+_item+"'";

    model->setQuery(query);
    return model;

}

void ui_atencion::on_pushButton_buscar_clicked()
{
    cleanWindow();//Borrando datos anteriores
    if(completingTextDoc_identidad->toPlainText().size() == 0){
        QMessageBox msgBox;
        msgBox.setText("Ingrese documento de identidad");
        completingTextDoc_identidad->setFocus();
        msgBox.exec();
        return;
    }

    dbconexion* s = dbconexion::getInstance();
    QSqlQuery query;
    query.prepare("SELECT * FROM paciente WHERE AFIL_DNI = ?");
    query.bindValue(0,completingTextDoc_identidad->toPlainText());
    QString ID,COD_RENAES,EESS,DISA,T_AFIL,NRO_AFIL,AFIL_DNI,F_AFIL,APEL_NOM,SEX,F_NACIMIENTO,EDAD,F_BAJA,NRO_HISTORIA,ETNIA;
    query.exec();
    {
        if(query.first())
        {
            //query.first();
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

            //LLENANDO DATOS
            ui->lineEdit_tdi->setText("2");
            //ui->lineEdit_doc_identidad->setText(AFIL_DNI);
            ui->lineEdit_diresa->setText("290");
            ui->lineEdit_t_afil->setText(T_AFIL);
            ui->lineEdit_numero->setText(AFIL_DNI);
            QStringList Apellidos_nombres = APEL_NOM.split(' ');
            QStringList procesado;
            for(int i =0;i<Apellidos_nombres.size();i++){
                if(Apellidos_nombres.at(i).size() >2 && Apellidos_nombres.at(i) != "VDA"  )
                    procesado.append(Apellidos_nombres.at(i));
            }


            if(procesado.size() > 0)
                ui->lineEdit_apellido_paterno->setText(procesado.at(0));
            if(procesado.size() > 1)
                ui->lineEdit_apellido_materno->setText(procesado.at(1));
            if(procesado.size() > 2)
                ui->lineEdit_nombres->setText(procesado.at(2));
            if(procesado.size() > 3)
                ui->lineEdit_otros_nombres->setText(procesado.at(3));

            if(SEX == "M")
                ui->radioButton_masulino->setChecked(true);
            if(SEX == "F")
                ui->radioButton_femenino->setChecked(true);

            //QString variable = F_NACIMIENTO.replace(QRegExp("[/, ]"), "-");
            QStringList fec = F_NACIMIENTO.split('/');
            QDate d1(fec.at(2).toInt(), fec.at(1).toInt(),fec.at(0).toInt());

            ui->lineEdit_num_historia_clinica->setText(NRO_HISTORIA);
            ui->lineEdit_etnia->setText(ETNIA);
            ui->dateEdit_fec_nac->setDate(d1);
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Paciente no encontrado");
            completingTextDoc_identidad->setFocus();
            msgBox.exec();
            return;
        }
    }



}

void ui_atencion::on_pushButton_search_clicked()
{
    ui->tableView_result_search->setModel(buscarPaciente(ui->lineEdit_search_dni->text()));

}





void ui_atencion::on_tableView_result_search_doubleClicked(const QModelIndex &index)
{
    ui->tableView_result_atenciones->setModel(buscarAtenciones(ui->tableView_result_search->model()->index(index.row(),0).data().toString()));
}


void ui_atencion::on_tableView_result_search_clicked(const QModelIndex &index)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM paciente WHERE AFIL_DNI = ?");
    query.bindValue(0,ui->tableView_result_search->model()->index(index.row(),0).data().toString());
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
        ui->lineEdit_s_establecimiento->setText(EESS);
        ui->lineEdit_s_datos_afil->setText(NRO_AFIL+" - "+F_AFIL+" - "+T_AFIL);
        ui->lineEdit_dni->setText(AFIL_DNI);
        ui->lineEdit_s_nombres->setText(APEL_NOM);
        ui->lineEdit_s_genero->setText(SEX);
        ui->lineEdit_s_fnacimiento->setText(F_NACIMIENTO);
        ui->lineEdit_s_edad->setText(EDAD);
        ui->lineEdit_s_fecbaja->setText(F_BAJA);
        ui->lineEdit_s_nrohistoria->setText(NRO_HISTORIA);
        ui->lineEdit_s_etnia->setText(ETNIA);
        //
        //LLENANDO DATOS
        ui->lineEdit_tdi->setText("2");
        completingTextDoc_identidad->setText(AFIL_DNI);
        ui->lineEdit_diresa->setText("290");
        ui->lineEdit_t_afil->setText(T_AFIL);
        ui->lineEdit_numero->setText(AFIL_DNI);
        QStringList Apellidos_nombres = APEL_NOM.split(' ');
        QStringList procesado;
        for(int i =0;i<Apellidos_nombres.size();i++){
            if(Apellidos_nombres.at(i).size() >2 && Apellidos_nombres.at(i) != "VDA"  )
                procesado.append(Apellidos_nombres.at(i));
        }

        if(procesado.size() > 0)
            ui->lineEdit_apellido_paterno->setText(procesado.at(0));
        if(procesado.size() > 1)
            ui->lineEdit_apellido_materno->setText(procesado.at(1));
        if(procesado.size() > 2)
            ui->lineEdit_nombres->setText(procesado.at(2));
        if(procesado.size() > 3)
            ui->lineEdit_otros_nombres->setText(procesado.at(3));

        if(SEX == "M")
            ui->radioButton_masulino->setChecked(true);
        if(SEX == "F")
            ui->radioButton_femenino->setChecked(true);

        //QString variable = F_NACIMIENTO.replace(QRegExp("[/, ]"), "-");
        QStringList fec = F_NACIMIENTO.split('/');
        QDate d1(fec.at(2).toInt(), fec.at(1).toInt(),fec.at(0).toInt());

        ui->lineEdit_num_historia_clinica->setText(NRO_HISTORIA);
        ui->lineEdit_etnia->setText(ETNIA);
        ui->dateEdit_fec_nac->setDate(d1);
    }


}
void ui_atencion::imprime()
{
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print Document");

    if (dialog->exec() == QDialog::Accepted)
    {
        QPainter painter;
        painter.begin(&printer);
        painter.setPen(Qt::black);
        //TAMANO DE FUENTE CALIBRADA PARA TMU220PA
        painter.setFont(QFont("Times",9));
        //painter.drawText(0,0,1000,1000, Qt::AlignLeft|Qt::AlignTop, impresora);
        painter.end();
    }


}

void ui_atencion::separa(QPainter &p, int x, int y, QString text, int factor)
{
    //factor 07 para 2mm
    //factor 15 para 4mm
    //factor 20 para 5mm
    //factor 21 para 6mm

    //int factor = 15;
    for(int i=0;i<text.size();i++){
        p.drawText(x,y,text.at(i));
        x+=factor;
    }
}

void ui_atencion::separaDate(QPainter &p, int x, int y, QString text, int factor)
{
    text.remove('/');
    for(int i=0;i<text.size();i++){
        p.drawText(x,y,text.at(i));
        x+=factor;
    }
}

void ui_atencion::separaDateYear(QPainter &p, int x, int y, QString text, int factor)
{
    text.remove('/');
    //text = text.remove(4,4);
    for(int i=0;i<text.size();i++){
        p.drawText(x,y,text.at(i));
        x+=factor;
    }
}

void ui_atencion::behaviorReferencia(bool s)
{
    ui->lineEdit_cod_renaes->setVisible(s);
    ui->lineEdit_nom_ipress->setVisible(s);
    ui->lineEdit_hoja_ref->setVisible(s);

    ui->label_8->setVisible(s);
    ui->label_9->setVisible(s);
    ui->label_10->setVisible(s);
    ui->label_11->setVisible(s);

    ui->lineEdit_cod_renaes->clear();
    ui->lineEdit_nom_ipress->clear();
    ui->lineEdit_hoja_ref->clear();
}

void ui_atencion::behaviorMaterna(bool s)
{
    ui->dateEdit_fec_parto->setEnabled(s);

}

void ui_atencion::on_pushButton_imprimir_clicked()
{
    QMessageBox msgBox;
    if(ui->radioButton_referencia->isChecked() && ui->lineEdit_hoja_ref->text().size() == 0){

        msgBox.setText("Ingrese NRO de REFENRECIA");
        ui->lineEdit_hoja_ref->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_tdi->text().size() == 0){

        msgBox.setText("Ingrese NRO de TDI");
        ui->lineEdit_tdi->setFocus();
        msgBox.exec();
        return;
    }
    if(completingTextDoc_identidad->toPlainText().size() == 0){

        msgBox.setText("Ingrese NRO de DNI");
        completingTextDoc_identidad->setFocus();        
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_diresa->text().size() == 0){

        msgBox.setText("Ingrese NRO de DIRESA");
        ui->lineEdit_diresa->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_t_afil->text().size() == 0){

        msgBox.setText("Ingrese tipo de afiliacion");
        ui->lineEdit_t_afil->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_numero->text().size() == 0){

        msgBox.setText("Ingrese numero ");
        ui->lineEdit_numero->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_apellido_paterno->text().size() == 0){

        msgBox.setText("Ingrese apellido paterno ");
        ui->lineEdit_apellido_paterno->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_apellido_materno->text().size() == 0){

        msgBox.setText("Ingrese apellido materno ");
        ui->lineEdit_apellido_materno->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_nombres->text().size() == 0){

        msgBox.setText("Ingrese apellido nombres ");
        ui->lineEdit_nombres->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->dateEdit_fec_nac->date() == QDate(2000,01,01)){

        msgBox.setText("Ingrese fecha de nacimiento ");
        ui->dateEdit_fec_nac->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_num_historia_clinica->text().size() == 0){

        msgBox.setText("Ingrese numero de historia clinica ");
        ui->lineEdit_num_historia_clinica->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_etnia->text().size() == 0){

        msgBox.setText("Ingrese etnia ");
        ui->lineEdit_etnia->setFocus();
        msgBox.exec();
        return;
    }




        QPrinter printer;
        QPrintDialog *dialog = new QPrintDialog(&printer);
        dialog->setWindowTitle("Print Document");
        //printer.setOutputFormat(QPrinter::PdfFormat);
        //printer.setOutputFileName("C:/Users/VIdal/Documents/sis/fuas/nonwritable.pdf");
        if (dialog->exec() == QDialog::Accepted)
        {
            QPainter painter;
            if (! painter.begin(&printer)) { // failed to open file
                qWarning("failed to open file, is it writable?");
            }


            //painter.drawText(665, 999, "Test");

            /*if (! printer.newPage()) {
                qWarning("failed in flushing page to disk, disk full?");
            }
            painter.drawText(1, 80, "Test 2");*/


            //CONSIGUIENDO MEDIDAS
            QSqlQuery query;
            query.prepare("SELECT * FROM medida WHERE ID = '1'");
            query.exec();
            double factorx,factory;
            {
                if(query.size()!=0)
                {
                    query.first();
                    QStringList salida;
                    //FACTOR_AJUSTE
                    salida= query.value(1).toString().split("-");
                    factorx=salida.at(0).toDouble();
                    factory=salida.at(1).toDouble();
                    //COD_EESS
                    if(ui->lineEdit_cod_eess->text().size() >0){
                    salida= query.value(2).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_cod_eess->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_cod_eess->text(),23);
                    }
                    //NOM_EESS
                    if(ui->lineEdit_nom_eess->text().size() >0)
                    {
                    salida= query.value(3).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_nom_eess->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_nom_eess->text(),12);
                    }
                    //IPRESS
                    if(ui->radioButton_ipress->isChecked())
                    {
                        salida= query.value(4).toString().split("-");
                        painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");
                    }
                    //ITINERANTE
                    if(ui->radioButton_itinerante->isChecked())
                    {
                    salida= query.value(5).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");
                    }

                    //OFERTA
                    if(ui->radioButton_oferta->isChecked())
                    {

                    salida= query.value(6).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");
                    }
                    //INTRAMURAL
                    if(ui->radioButton_intramural->isChecked())
                    {
                    salida= query.value(7).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");
                    }
                    //EXTRAMURAL
                    if(ui->radioButton_extramural->isChecked())
                    {
                    salida= query.value(8).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");
                    }
                    //AMBULATORIA
                    if(ui->radioButton_ambulatoria->isChecked())
                    {
                    salida= query.value(9).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");
                    }
                    //REFERENCIA
                    if(ui->radioButton_referencia->isChecked())
                    {
                    salida= query.value(10).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");
                    }
                    //EMERGENCIA
                    if(ui->radioButton_emergencia->isChecked())
                    {
                    salida= query.value(11).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");

                    }
                    //COD_RENAES
                    if(ui->lineEdit_cod_renaes->text().size() >0){
                    salida= query.value(12).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_cod_renaes->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_cod_renaes->text(),12);
                    }
                    //NOMBRE_IPRESS
                    if(ui->lineEdit_nom_ipress->text().size() >0){
                    salida= query.value(13).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_nom_ipress->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_nom_ipress->text(),12);
                    }

                    //HOJA_REFERENCIA
                    if(ui->lineEdit_hoja_ref->text().size() >0){
                    salida= query.value(14).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_hoja_ref->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_hoja_ref->text(),12);
                    }
                    //TDI
                    if(ui->lineEdit_tdi->text().size() >0){
                    salida= query.value(15).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_tdi->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_tdi->text(),12);
                    }
                    //DOCUMENTO_IDENTIDAD
                    if(completingTextDoc_identidad->toPlainText().size() >0){
                    salida= query.value(16).toString().split("-");

                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),completingTextDoc_identidad->toPlainText());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),completingTextDoc_identidad->toPlainText(),15);

                    }
                    //DIRESA
                    if(ui->lineEdit_cod_eess->text().size() >0){
                    salida= query.value(17).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_diresa->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_diresa->text(),12);


                    }
                    //NUMERO
                    if(ui->lineEdit_numero->text().size() >0){
                    salida= query.value(18).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_numero->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_t_afil->text()+ui->lineEdit_numero->text(),15);



                    }
                    //INSTITUCION
                    if(ui->lineEdit_institucion->text().size() >0){
                    salida= query.value(19).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_institucion->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_institucion->text(),3);


                    }
                    //COD_SEGURO
                    if(ui->lineEdit_cod_seg->text().size() >0){
                    salida= query.value(20).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_cod_seg->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_cod_seg->text(),15);
                    }
                    //APELL_PATERNO
                    if(ui->lineEdit_apellido_paterno->text().size() >0){
                    salida= query.value(21).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_apellido_paterno->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_apellido_paterno->text(),20);



                    }
                    //APELL_MATERNO
                    if(ui->lineEdit_apellido_materno->text().size() >0){
                    salida= query.value(22).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_apellido_materno->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_apellido_materno->text(),20);



                    }
                    //NOMBRES
                    if(ui->lineEdit_nombres->text().size() >0){
                    salida= query.value(23).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_nombres->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_nombres->text(),20);



                    }
                    //OTROS_NOMBRES
                    if(ui->lineEdit_otros_nombres->text().size() >0){
                    salida= query.value(24).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_otros_nombres->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_otros_nombres->text(),20);



                    }
                    //SEX_M
                    if(ui->radioButton_masulino->isChecked())
                    {
                    salida= query.value(25).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");



                    }
                    //SEX_F
                    if(ui->radioButton_femenino->isChecked())
                    {
                    salida= query.value(26).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");



                    }
                    //GESTANTE
                    if(ui->radioButton_gestante->isChecked())
                    {
                    salida= query.value(27).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");



                    }
                    //PUERPERA
                    if(ui->radioButton_puerpera->isChecked())
                    {
                    salida= query.value(28).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");

                    }
                    //FEC_PARTO

                    if(ui->dateEdit_fec_parto->date() != QDate(2000,01,01)){
                        salida= query.value(29).toString().split("-");
                        //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->dateEdit_fec_parto->text());
                        separaDateYear(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->dateEdit_fec_parto->text(),21);

                    }

                    //FEC_NACIMIENTO
                    if(ui->dateEdit_fec_nac->date() != QDate(2000,01,01)){
                    salida= query.value(30).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->dateEdit_fec_nac->text());
                    separaDate(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->dateEdit_fec_nac->text(),21);


                    }
                    //FEC_FALLECIMIENTO
                    if(ui->dateEdit_fec_falle->date() != QDate(2000,01,01)){
                    salida= query.value(31).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->dateEdit_fec_falle->text());
                    separaDate(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->dateEdit_fec_falle->text(),21);

                    }
                    //NUM_HISTORIA
                    if(ui->lineEdit_num_historia_clinica->text().size() >0){
                    salida= query.value(32).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_num_historia_clinica->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_num_historia_clinica->text(),12);


                    }
                    //ETNIA
                    if(ui->lineEdit_etnia->text().size() >0){
                    salida= query.value(33).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_etnia->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_etnia->text(),12);
                    }
                    //DNI_CNV_AFIL_RN
                    if(ui->lineEdit_dni_cnv_afiliacion_rn->text().size() >0){
                    salida= query.value(34).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_dni_cnv_afiliacion_rn->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_dni_cnv_afiliacion_rn->text(),12);


                    }
                    //FECHA DE ATENCION
                    salida= query.value(35).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->dateEdit_fec_atencion->text());
                    separaDateYear(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->dateEdit_fec_atencion->text(),21);

                    //painter.drawText(int(44),int(444),ui->dateEdit_fec_nac->text());
                    //COD DE PRESTACION
                    if(ui->lineEdit_cod_prestacion->text().size() >0){
                    salida= query.value(36).toString().split("-");
                    //painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_cod_prestacion->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_cod_prestacion->text(),12);
                    //painter.drawText(int(355),int(444),"COD");
                    }
                    //ATENCION DIRECTA
                    salida= query.value(37).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");
                    //painter.drawText(int(110),int(506),"AT");
                    //ASEGURADO
                    salida= query.value(38).toString().split("-");
                    painter.drawText(int(salida.at(0).toInt()),int(salida.at(1).toInt()),"X");
                    //painter.drawText(int(414),int(99),"AS");

                    //COD_RENAES CONTRAREFERNCIA
                    if(ui->lineEdit_cod_renaes->text().size() >0){
                    salida= query.value(39).toString().split("-");
                    //painter.drawText(44,615,ui->lineEdit_cod_renaes->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_cod_renaes->text(),12);
                    }
                    //NOMBRE_IPRESS CONTRAREFERNCIA
                    if(ui->lineEdit_nom_ipress->text().size() >0){
                    salida= query.value(40).toString().split("-");
                    //painter.drawText(298,615,ui->lineEdit_nom_ipress->text());
                    separa(painter,int(salida.at(0).toInt()),int(salida.at(1).toInt()),ui->lineEdit_nom_ipress->text(),12);
                    }
                }
            }

            painter.end();
        }

}

void ui_atencion::on_lineEdit_doc_identidad_returnPressed()
{
    //ui->pushButton_buscar->click();
}

void ui_atencion::on_lineEdit_search_dni_returnPressed()
{
    ui->pushButton_search->click();
}

void ui_atencion::on_pushButton_nuevo_paciente_clicked()
{
    ui_paciente *form_paciente = new ui_paciente;
    form_paciente->setWindowTitle("Nuevo Paciente");
    form_paciente->loadDefaultNew();
    form_paciente->show();


}

void ui_atencion::on_pushButton_edit_data_clicked()
{
    ui_paciente *form_paciente = new ui_paciente;
    form_paciente->setWindowTitle("Editar datos de paciente");
    form_paciente->setDni(ui->lineEdit_dni->text());
    form_paciente->loadDefaultEdit();
    form_paciente->show();
}

void ui_atencion::on_lineEdit_cod_renaes_textEdited(const QString &arg1)
{
    ui->lineEdit_nom_ipress->setText(hash[arg1.toInt()]);
}

void ui_atencion::on_radioButton_referencia_clicked(bool checked)
{
    behaviorReferencia(checked);
}

void ui_atencion::on_radioButton_referencia_toggled(bool checked)
{
    behaviorReferencia(checked);

}

void ui_atencion::cleanWindow()
{
    ui->lineEdit_cod_renaes->clear();
    ui->lineEdit_nom_ipress->clear();
    ui->lineEdit_hoja_ref->clear();
    ui->lineEdit_tdi->setText("2");
    ui->lineEdit_diresa->setText("290");
    ui->lineEdit_numero->setText(completingTextDoc_identidad->toPlainText());
    ui->lineEdit_institucion->clear();
    ui->lineEdit_cod_seg->clear();
    ui->lineEdit_apellido_paterno->clear();
    ui->lineEdit_apellido_materno->clear();
    ui->lineEdit_nombres->clear();
    ui->lineEdit_otros_nombres->clear();    
    ui->dateEdit_fec_parto->setDate(QDate(2000,01,01));
    ui->dateEdit_fec_nac->setDate(QDate(2000,01,01));
    ui->dateEdit_fec_falle->setDate(QDate(2000,01,01));
    ui->lineEdit_num_historia_clinica->setText(completingTextDoc_identidad->toPlainText());    
    ui->lineEdit_etnia->setText("80");
    ui->lineEdit_dni_cnv_afiliacion_rn->clear();
    ui->lineEdit_cod_prestacion->clear();
    ui->lineEdit_t_afil->setText("1");
}

void ui_atencion::on_pushButton_guardar_paciente_clicked()
{

    //VALIDACION
    QMessageBox msgBox;

    if(ui->lineEdit_tdi->text().size() == 0){

        msgBox.setText("Ingrese NRO de TDI");
        ui->lineEdit_tdi->setFocus();
        msgBox.exec();
        return;
    }
    if(completingTextDoc_identidad->toPlainText().size() == 0){

        msgBox.setText("Ingrese NRO de DNI");        
        completingTextDoc_identidad->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_diresa->text().size() == 0){

        msgBox.setText("Ingrese NRO de DIRESA");
        ui->lineEdit_diresa->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_t_afil->text().size() == 0){

        msgBox.setText("Ingrese tipo de afiliacion");
        ui->lineEdit_t_afil->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_numero->text().size() == 0){

        msgBox.setText("Ingrese numero ");
        ui->lineEdit_numero->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_apellido_paterno->text().size() == 0){

        msgBox.setText("Ingrese apellido paterno ");
        ui->lineEdit_apellido_paterno->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_apellido_materno->text().size() == 0){

        msgBox.setText("Ingrese apellido materno ");
        ui->lineEdit_apellido_materno->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_nombres->text().size() == 0){

        msgBox.setText("Ingrese apellido nombres ");
        ui->lineEdit_nombres->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->dateEdit_fec_nac->date() == QDate(2000,01,01)){

        msgBox.setText("Ingrese fecha de nacimiento ");
        ui->dateEdit_fec_nac->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_num_historia_clinica->text().size() == 0){

        msgBox.setText("Ingrese numero de historia clinica ");
        ui->lineEdit_num_historia_clinica->setFocus();
        msgBox.exec();
        return;
    }
    if(ui->lineEdit_etnia->text().size() == 0){

        msgBox.setText("Ingrese etnia ");
        ui->lineEdit_etnia->setFocus();
        msgBox.exec();
        return;
    }
    QSqlQuery q;
    QString query;
    QString SEX,F_AFIL,F_NACIMIENTO,F_BAJA;
    if(ui->radioButton_masulino->isChecked()){
        SEX="M";
    }
    if(ui->radioButton_femenino->isChecked()){
        SEX="F";
    }
        F_AFIL=ui->dateEdit_fec_atencion->text();
        F_NACIMIENTO=ui->dateEdit_fec_nac->text();
        F_BAJA=ui->dateEdit_fec_atencion->text();
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
                ui->lineEdit_nom_eess->text()+"','"+
                ui->lineEdit_diresa->text()+"','"+
                ui->lineEdit_t_afil->text()+"','"+
                completingTextDoc_identidad->toPlainText()+"','"+
                completingTextDoc_identidad->toPlainText()+"','"+
                F_AFIL+"','"+
                ui->lineEdit_apellido_paterno->text()+" "+ui->lineEdit_apellido_materno->text()+" "+ui->lineEdit_nombres->text()+" "+ui->lineEdit_otros_nombres->text()+"','"+
                SEX+"','"+
                F_NACIMIENTO+"','"+
                "0"+"','"+//EDAD
                F_BAJA+"','"+
                ui->lineEdit_num_historia_clinica->text()+"','"+
                ui->lineEdit_etnia->text()+"')";

    if(!q.exec(query)){
        qDebug() <<q.lastError().text();
    }
    else{
            QMessageBox msgBox;
            msgBox.setText("Datos Guardados Correctamente");
            msgBox.exec();

            QSqlQueryModel *model = new QSqlQueryModel;
            QString query;
            query= "SELECT AFIL_DNI FROM paciente";
            model->setQuery(query);
            completer = new QCompleter(this);
            completer->setModel(model);
            completingTextDoc_identidad->setCompleter(completer);
    }
}

void ui_atencion::on_lineEdit_descripcion1_textEdited(const QString &arg1)
{
    /*dbconexion* s = dbconexion::getInstance();
    QSqlQuery query;
    query.prepare("SELECT * FROM cie where ID=10");
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

        }
    }
    ui->lineEdit_descripcion2->setText(NOMBRE_IPRESS);*/


}

void ui_atencion::on_pushButton_guardar_profesional_clicked()
{
    //VALIDACION
    QMessageBox msgBox;

    if(completingTextDni_profe->toPlainText().size() == 0 || completingTextDni_profe->toPlainText().size() < 7){

        msgBox.setText("Ingrese NRO de DNI correctamente");
        completingTextDni_profe->setFocus();
        msgBox.exec();
        return;
    }
    if(completingTextNombre_profe->toPlainText().size() == 0){

        msgBox.setText("Ingrese NOMBRE de profesional");
        completingTextNombre_profe->setFocus();
        msgBox.exec();
        return;
    }
    if(completingTextNro_colegiatura->toPlainText().size() == 0){

        msgBox.setText("Ingrese NRO de colegiatura");
        completingTextNro_colegiatura->setFocus();
        msgBox.exec();
        return;
    }

    QSqlQuery q;
    QString query;
    QString DNI,NOMBRE,COLEGIATURA,CODIGO,ESPECIALIDAD,RNE,EGRESADO;
    DNI = completingTextDni_profe->toPlainText();
    NOMBRE = completingTextNombre_profe->toPlainText();
    COLEGIATURA = completingTextNro_colegiatura->toPlainText();
    CODIGO = QString::number(ui->comboBox_cod_responsable->currentIndex());
    ESPECIALIDAD = ui->lineEdit_especialidad->text();
    RNE = ui->lineEdit_nro_rne->text();
    EGRESADO = ui->lineEdit_egresado->text();
    if(ui->pushButton_guardar_profesional->text() == "Nuevo Profesional")
    {
        query = "INSERT OR IGNORE INTO profesional ("
                "DNI,"
                "NOMBRE,"
                "COLEGIATURA,"
                "CODIGO,"
                "ESPECIALIDAD,"
                "RNE,"
                "EGRESADO"
                ") VALUES('"+DNI+"','"+
                NOMBRE+"','"+
                COLEGIATURA+"','"+
                CODIGO+"','"+
                ESPECIALIDAD+"','"+
                RNE+"','"+
                EGRESADO+
                +"')";




        if(!q.exec(query)){
            qDebug() <<q.lastError().text();
        }
        else{
                QMessageBox msgBox;
                msgBox.setText("Datos de profesional guardados correctamente");
                msgBox.exec();
        }
    }
    if(ui->pushButton_guardar_profesional->text() == "Actualizar Profesional")
    {
        query = "UPDATE OR IGNORE profesional SET "
                "NOMBRE ='"+NOMBRE+"',"+
                "COLEGIATURA ='"+COLEGIATURA+"',"+
                "CODIGO ='"+CODIGO+"',"+
                "ESPECIALIDAD ='"+ESPECIALIDAD+"',"+
                "RNE ='"+RNE+"',"+
                "EGRESADO ='"+EGRESADO+"'"+
                " WHERE DNI = '"+DNI+"'";




        if(!q.exec(query)){
            qDebug() <<q.lastError().text();
        }
        else{
                QMessageBox msgBox;
                msgBox.setText("Datos de profesional actualizados correctamente");
                msgBox.exec();
        }
    }


}

void ui_atencion::createDescripcionCie()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query;

    query= "SELECT DESC_ENF FROM cie";
    model->setQuery(query);


    completer = new QCompleter(this);
    completer->setModel(model);
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);

    completingTextEdit1 = new TextEdit;
    completingTextEdit1->setCompleter(completer);
    completingTextEdit1->setMaximumHeight(28);

    completingTextEdit2 = new TextEdit;
    completingTextEdit2->setCompleter(completer);
    completingTextEdit2->setMaximumHeight(28);

    completingTextEdit3 = new TextEdit;
    completingTextEdit3->setCompleter(completer);
    completingTextEdit3->setMaximumHeight(28);

    completingTextEdit4 = new TextEdit;
    completingTextEdit4->setCompleter(completer);
    completingTextEdit4->setMaximumHeight(28);

    completingTextEdit5 = new TextEdit;
    completingTextEdit5->setCompleter(completer);
    completingTextEdit5->setMaximumHeight(28);

    ui->gridLayout_4->addWidget(completingTextEdit1,1,0);
    ui->gridLayout_4->addWidget(completingTextEdit2,2,0);
    ui->gridLayout_4->addWidget(completingTextEdit3,3,0);
    ui->gridLayout_4->addWidget(completingTextEdit4,4,0);
    ui->gridLayout_4->addWidget(completingTextEdit5,5,0);

}

void ui_atencion::createCodCie()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query;


    query= "SELECT COD_CAT FROM cie";
    model->setQuery(query);

    completer = new QCompleter(this);
    completer->setModel(model);
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);

    completingTextCie1 = new TextEdit;
    completingTextCie1->setCompleter(completer);
    completingTextCie1->setMaximumHeight(28);
    completingTextCie1->setMaximumWidth(60);

    completingTextCie2 = new TextEdit;
    completingTextCie2->setCompleter(completer);
    completingTextCie2->setMaximumHeight(28);
    completingTextCie2->setMaximumWidth(60);

    completingTextCie3 = new TextEdit;
    completingTextCie3->setCompleter(completer);
    completingTextCie3->setMaximumHeight(28);
    completingTextCie3->setMaximumWidth(60);

    completingTextCie4 = new TextEdit;
    completingTextCie4->setCompleter(completer);
    completingTextCie4->setMaximumHeight(28);
    completingTextCie4->setMaximumWidth(60);

    completingTextCie5 = new TextEdit;
    completingTextCie5->setCompleter(completer);
    completingTextCie5->setMaximumHeight(28);
    completingTextCie5->setMaximumWidth(60);

    ui->gridLayout_4->addWidget(completingTextCie1,1,4);
    ui->gridLayout_4->addWidget(completingTextCie2,2,4);
    ui->gridLayout_4->addWidget(completingTextCie3,3,4);
    ui->gridLayout_4->addWidget(completingTextCie4,4,4);
    ui->gridLayout_4->addWidget(completingTextCie5,5,4);
}

void ui_atencion::createDoc_indetidad()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query;
    query= "SELECT AFIL_DNI FROM paciente";
    model->setQuery(query);
    completer = new QCompleter(this);
    completer->setModel(model);
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    completingTextDoc_identidad = new TextEdit;
    completingTextDoc_identidad->setCompleter(completer);
    completingTextDoc_identidad->setMaximumHeight(28);
    completingTextDoc_identidad->setMaximumWidth(270);
    //ADD LATOUT
    ui->gridLayout->addWidget(completingTextDoc_identidad,8,2);



}




void ui_atencion::conexionSlot()
{
    connect(completingTextEdit1, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextEdit1()));
    connect(completingTextCie1, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextCie1()));

    connect(completingTextEdit2, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextEdit2()));
    connect(completingTextCie2, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextCie2()));

    connect(completingTextEdit3, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextEdit3()));
    connect(completingTextCie3, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextCie3()));

    connect(completingTextEdit4, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextEdit4()));
    connect(completingTextCie4, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextCie4()));

    connect(completingTextEdit5, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextEdit5()));
    connect(completingTextCie5, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextCie5()));

    //SLOT RESPONSABLE ATENCION

    connect(completingTextDni_profe, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextDni_profe()));
    connect(completingTextNombre_profe, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextNombre_profe()));
    connect(completingTextNro_colegiatura, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextNro_colegiatura()));

    //SLOT DNI SEARCH PACIENTE
    connect(completingTextDoc_identidad, SIGNAL(textChanged()), this, SLOT(on_finised_editing_completingTextDoc_identidad()));
}

void ui_atencion::createResponsable()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQueryModel *model1 = new QSqlQueryModel;
    QSqlQueryModel *model2 = new QSqlQueryModel;

    completer = new QCompleter(this);
    completer1 = new QCompleter(this);
    completer2 = new QCompleter(this);
    QString query;

    query= "SELECT DNI FROM profesional";
    model->setQuery(query);



    completer->setModel(model);
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);

    completingTextDni_profe = new TextEdit;
    completingTextDni_profe->setCompleter(completer);
    completingTextDni_profe->setMaximumHeight(28);
    completingTextDni_profe->setMaximumWidth(100);

    query= "SELECT NOMBRE FROM profesional";
    model1->setQuery(query);
    completer1->setModel(model1);

    completingTextNombre_profe = new TextEdit;
    completingTextNombre_profe->setCompleter(completer1);
    completingTextNombre_profe->setMaximumHeight(28);


    query= "SELECT COLEGIATURA FROM profesional";
    model2->setQuery(query);
    completer2->setModel(model2);

    completingTextNro_colegiatura = new TextEdit;
    completingTextNro_colegiatura->setCompleter(completer2);
    completingTextNro_colegiatura->setMaximumHeight(28);
    //completingTextNro_colegiatura->setMaximumWidth(100);

    //LAYOUT
    ui->gridLayout_5->addWidget(completingTextDni_profe,0,1);
    ui->gridLayout_5->addWidget(completingTextNombre_profe,0,3);
    ui->gridLayout_5->addWidget(completingTextNro_colegiatura,0,5);

    //NEW LAYOUT


}

void ui_atencion::on_finised_editing_completingTextEdit1()
{
    if(completingTextEdit1->toPlainText().size() > 5 && activatedText1){
        qDebug()<<"CONSULTANDO";
        QSqlQuery query;
        QString consulta = "SELECT COD_CAT FROM cie where UPPER(DESC_ENF) =UPPER('"+completingTextEdit1->toPlainText()+"')";
        query.prepare(consulta);
        QString ID;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                query.first();
                ID=query.value(0).toString();
                completingTextCie1->setText(ID);
            }
        }
    }
    else {
        activatedText1 = true;
        activatedCie1 = false;
    }
}

void ui_atencion::on_finised_editing_completingTextCie1()
{
    if(completingTextCie1->toPlainText().size() > 3 && activatedCie1){
        QSqlQuery query;
        QString consulta = "SELECT DESC_ENF FROM cie where COD_CAT = '"+completingTextCie1->toPlainText()+"'";
        query.prepare(consulta);
        //query.bindValue(0,numeroDocumento);
        QString ID;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                query.first();
                ID=query.value(0).toString();
                completingTextEdit1->setText(ID);
            }
        }

    }
    else {
        activatedText1 = false;
        activatedCie1 = true;
    }

}

void ui_atencion::on_finised_editing_completingTextEdit2()
{
    if(completingTextEdit2->toPlainText().size() > 5 && activatedText2){
        QSqlQuery query;
        QString consulta = "SELECT COD_CAT FROM cie where UPPER(DESC_ENF) = UPPER('"+completingTextEdit2->toPlainText()+"')";
        query.prepare(consulta);
        QString ID;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                query.first();
                ID=query.value(0).toString();
                qDebug()<<ID;
                completingTextCie2->setText(ID);
            }
        }        
    }
    else {
        activatedText2 = true;
        activatedCie2 = false;
    }

}

void ui_atencion::on_finised_editing_completingTextCie2()
{
    if(completingTextCie2->toPlainText().size() > 3 && activatedCie2){
        QSqlQuery query;
        QString consulta = "SELECT DESC_ENF FROM cie where COD_CAT = '"+completingTextCie2->toPlainText()+"'";
        query.prepare(consulta);
        //query.bindValue(0,numeroDocumento);
        QString ID;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                query.first();
                ID=query.value(0).toString();
                completingTextEdit2->setText(ID);
            }
        }                
    }
    else {
        activatedCie2 = true;
        activatedText2 = false;
    }

}
void ui_atencion::on_finised_editing_completingTextEdit3()
{
    if(completingTextEdit3->toPlainText().size() > 5 && activatedText3){
        QSqlQuery query;
        QString consulta = "SELECT COD_CAT FROM cie where UPPER(DESC_ENF) = UPPER('"+completingTextEdit3->toPlainText()+"')";
        query.prepare(consulta);
        QString ID;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                query.first();
                ID=query.value(0).toString();
                completingTextCie3->setText(ID);
            }
        }        
    }
    else {
        activatedText3 = true;
        activatedCie3 = false;
    }

}

void ui_atencion::on_finised_editing_completingTextCie3()
{
    if(completingTextCie3->toPlainText().size() > 3 && activatedCie3){
        QSqlQuery query;
        QString consulta = "SELECT DESC_ENF FROM cie where COD_CAT = '"+completingTextCie3->toPlainText()+"'";
        query.prepare(consulta);
        //query.bindValue(0,numeroDocumento);
        QString ID;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                query.first();
                ID=query.value(0).toString();
            }
        }
        else {
            completingTextEdit3->setText("No");
        }

    }

}
void ui_atencion::on_finised_editing_completingTextEdit4()
{
    if(completingTextEdit4->toPlainText().size() > 5 && activatedText4){
        QSqlQuery query;
        QString consulta = "SELECT COD_CAT FROM cie where UPPER(DESC_ENF) = UPPER('"+completingTextEdit4->toPlainText()+"')";
        query.prepare(consulta);
        QString ID;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                query.first();
                ID=query.value(0).toString();
                completingTextCie4->setText(ID);
            }
        }
    }
    else {
        activatedText4 = true;
        activatedCie4 = false;
    }

}

void ui_atencion::on_finised_editing_completingTextCie4()
{
    if(completingTextCie4->toPlainText().size() > 3 && activatedCie4){
        QSqlQuery query;
        QString consulta = "SELECT DESC_ENF FROM cie where COD_CAT = '"+completingTextCie4->toPlainText()+"'";
        query.prepare(consulta);
        //query.bindValue(0,numeroDocumento);
        QString ID;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                query.first();
                ID=query.value(0).toString();
                completingTextEdit4->setText(ID);
            }
        }
     }
    else {
        activatedCie4 = true;
        activatedText4 = false;
    }

}
void ui_atencion::on_finised_editing_completingTextEdit5()
{
    if(completingTextEdit5->toPlainText().size() > 5 && activatedText5){
        QSqlQuery query;
        QString consulta = "SELECT COD_CAT FROM cie where UPPER(DESC_ENF) = UPPER('"+completingTextEdit5->toPlainText()+"')";
        query.prepare(consulta);
        QString ID;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                query.first();
                ID=query.value(0).toString();
                completingTextCie5->setText(ID);
            }
        }        
    }
    else {
        activatedText5 = true;
        activatedCie5 = false;
    }

}

void ui_atencion::on_finised_editing_completingTextCie5()
{
    if(completingTextCie5->toPlainText().size() > 3 && activatedCie5){
        QSqlQuery query;
        QString consulta = "SELECT DESC_ENF FROM cie where COD_CAT = '"+completingTextCie5->toPlainText()+"'";
        query.prepare(consulta);
        //query.bindValue(0,numeroDocumento);
        QString ID;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                query.first();
                ID=query.value(0).toString();
                completingTextEdit5->setText(ID);
            }
        }
    }
    else {
        activatedText5 = false;
        activatedCie5 = true;
    }

}

void ui_atencion::on_finised_editing_completingTextDni_profe()
{
    if(completingTextDni_profe->toPlainText().size() > 6 && activareDni_profe){
        QSqlQuery query;
        QString consulta = "SELECT NOMBRE, COLEGIATURA, CODIGO, ESPECIALIDAD, RNE, EGRESADO FROM profesional where DNI = '"+completingTextDni_profe->toPlainText()+"'";
        query.prepare(consulta);
        QString NOMBRE,COLEGIATURA, CODIGO, ESPECIALIDAD, RNE, EGRESADO;
        qDebug()<<"iniciando consulta";
        if(query.exec())
        {
            if(query.size()!=0)
            {
                if(query.first()){

                    NOMBRE=query.value(0).toString();
                    COLEGIATURA=query.value(1).toString();
                    CODIGO=query.value(2).toString();
                    ESPECIALIDAD=query.value(3).toString();
                    RNE=query.value(4).toString();
                    EGRESADO=query.value(5).toString();


                    completingTextNombre_profe->setText(NOMBRE);
                    completingTextNro_colegiatura->setText(COLEGIATURA);

                    ui->comboBox_cod_responsable->setCurrentIndex(CODIGO.toInt());
                    ui->lineEdit_especialidad->setText(ESPECIALIDAD);
                    ui->lineEdit_nro_rne->setText(RNE);
                    ui->lineEdit_egresado->setText(EGRESADO);
                    qDebug()<<"Consultando DNI";
                    ui->pushButton_guardar_profesional->setText("Actualizar Profesional");


                }

            }
        }        
    }
    else {
        activareDni_profe=true;
        activateNombre_profe=false;
        activateNro_colegiatura=false;
        qDebug()<<"termino dni";
        ui->pushButton_guardar_profesional->setText("Nuevo Profesional");
    }
}

void ui_atencion::on_finised_editing_completingTextNombre_profe()
{
    if(completingTextNombre_profe->toPlainText().size() > 6 && activateNombre_profe){
        QSqlQuery query;
        QString consulta = "SELECT DNI, COLEGIATURA FROM profesional where UPPER(NOMBRE) = UPPER('"+completingTextNombre_profe->toPlainText()+"')";
        query.prepare(consulta);
        QString DNI,COLEGIATURA;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                if(query.first()){
                    DNI=query.value(0).toString();
                    COLEGIATURA=query.value(1).toString();
                    qDebug()<<DNI;
                    qDebug()<<COLEGIATURA;
                    completingTextDni_profe->setText(DNI);
                    completingTextNro_colegiatura->setText(COLEGIATURA);
                    qDebug()<<"Consultando NOMBRE PROFESIONAL";
                    ui->pushButton_guardar_profesional->setText("Actualizar Profesional");
                }

            }
        }        
    }
    else {
        activareDni_profe=false;
        activateNombre_profe=true;
        activateNro_colegiatura=false;
        qDebug()<<"termino nombre";
        ui->pushButton_guardar_profesional->setText("Nuevo Profesional");
    }
}

void ui_atencion::on_finised_editing_completingTextNro_colegiatura()
{
    if(completingTextNro_colegiatura->toPlainText().size() > 4 && activateNro_colegiatura){
        QSqlQuery query;
        QString consulta = "SELECT NOMBRE, DNI FROM profesional where COLEGIATURA = '"+completingTextNro_colegiatura->toPlainText()+"'";
        query.prepare(consulta);
        QString NOMBRE,DNI;
        if(query.exec())
        {
            if(query.size()!=0)
            {
                if(query.first()){
                    NOMBRE=query.value(0).toString();
                    DNI=query.value(1).toString();
                    completingTextNombre_profe->setText(NOMBRE);
                    completingTextDni_profe->setText(DNI);
                    qDebug()<<"Consultando COLEGIATURA";
                    ui->pushButton_guardar_profesional->setText("Actualizar Profesional");
                }

            }
        }        
    }
    else {
        activareDni_profe=false;
        activateNombre_profe=false;
        activateNro_colegiatura=true;
        qDebug()<<"termino colegiatura";
        ui->pushButton_guardar_profesional->setText("Nuevo Profesional");
    }
}

void ui_atencion::on_finised_editing_completingTextDoc_identidad()
{
    qDebug()<<"Finished Editing";
    if(completingTextDoc_identidad->toPlainText().size() < 8){
        qDebug()<<"Tamaño menor a 8 DNI";
        return;
    }
    qDebug()<<"Pasando a consulta";
    QSqlQuery query;
    query.prepare("SELECT * FROM paciente WHERE AFIL_DNI = ?");
    query.bindValue(0,completingTextDoc_identidad->toPlainText());
    QString ID,COD_RENAES,EESS,DISA,T_AFIL,NRO_AFIL,AFIL_DNI,F_AFIL,APEL_NOM,SEX,F_NACIMIENTO,EDAD,F_BAJA,NRO_HISTORIA,ETNIA;
    query.exec();
    {
        qDebug()<<"Executando query";
        if(query.first())
        {
            //query.first();
            qDebug()<<"Query First";
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
            cleanWindow();//Borrando datos anteriores
            //LLENANDO DATOS
            ui->lineEdit_tdi->setText("2");
            //ui->lineEdit_doc_identidad->setText(AFIL_DNI);
            ui->lineEdit_diresa->setText("290");
            ui->lineEdit_t_afil->setText(T_AFIL);
            ui->lineEdit_numero->setText(AFIL_DNI);
            QStringList Apellidos_nombres = APEL_NOM.split(' ');
            QStringList procesado;
            for(int i =0;i<Apellidos_nombres.size();i++){
                if(Apellidos_nombres.at(i).size() >2 && Apellidos_nombres.at(i) != "VDA"  )
                    procesado.append(Apellidos_nombres.at(i));
            }


            if(procesado.size() > 0)
                ui->lineEdit_apellido_paterno->setText(procesado.at(0));
            if(procesado.size() > 1)
                ui->lineEdit_apellido_materno->setText(procesado.at(1));
            if(procesado.size() > 2)
                ui->lineEdit_nombres->setText(procesado.at(2));
            if(procesado.size() > 3)
                ui->lineEdit_otros_nombres->setText(procesado.at(3));

            if(SEX == "M")
                ui->radioButton_masulino->click();
            if(SEX == "F")
                ui->radioButton_femenino->click();

            //QString variable = F_NACIMIENTO.replace(QRegExp("[/, ]"), "-");
            QStringList fec = F_NACIMIENTO.split('/');
            QDate d1(fec.at(2).toInt(), fec.at(1).toInt(),fec.at(0).toInt());

            ui->lineEdit_num_historia_clinica->setText(NRO_HISTORIA);
            ui->lineEdit_etnia->setText(ETNIA);
            ui->dateEdit_fec_nac->setDate(d1);
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Paciente no encontrado");
            completingTextDoc_identidad->setFocus();
            msgBox.exec();
            cleanWindow();//Borrando datos anteriores
            return;
        }
    }
}

void ui_atencion::on_pushButton_imprimir_diagnostico_clicked()
{

}

void ui_atencion::on_radioButton_clicked(bool checked)
{
    if(checked){
        ui->dateEdit_fec_parto->setEnabled(false);
    }


}

void ui_atencion::on_radioButton_gestante_clicked(bool checked)
{
    ui->dateEdit_fec_parto->setEnabled(checked);

}

void ui_atencion::on_radioButton_puerpera_clicked(bool checked)
{
    ui->dateEdit_fec_parto->setEnabled(checked);
}

void ui_atencion::on_radioButton_femenino_clicked(bool checked)
{
    ui->radioButton_gestante->setEnabled(checked);
    ui->radioButton_puerpera->setEnabled(checked);
}

void ui_atencion::on_radioButton_masulino_clicked(bool checked)
{
    ui->radioButton_gestante->setEnabled(!checked);
    ui->radioButton_puerpera->setEnabled(!checked);
    ui->radioButton->click();
}

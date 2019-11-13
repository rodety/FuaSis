#include "ui_configuracion.h"
#include "ui_ui_configuracion.h"
#include <QFileDialog>
#include "dbmanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <qaxobject.h>
#include "dbconexion.h"
#include <QTableWidget>
#include <QMessageBox>

ui_configuracion::ui_configuracion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_configuracion)
{
    ui->setupUi(this);
    if(ui->label_afiliados->text().size() ==0){
        ui->pushButton_proc_afil->setEnabled(false);
    }
    else{
        ui->pushButton_proc_afil->setEnabled(true);
    }
    if(ui->label_atenciones->text().size() ==0){
        ui->pushButton_proc_atenciones->setEnabled(false);
    }
    else{
        ui->pushButton_proc_atenciones->setEnabled(true);
    }
    if(ui->label_cie->text().size() ==0){
        ui->pushButton_proc_cie->setEnabled(false);
    }
    else{
        ui->pushButton_proc_cie->setEnabled(true);
    }
    formatTableWidget();

    //QObject::connect ((this->ui_configuracion, SIGNAL (showMessage (QString &))), this, SLOT (updateMessage (QString &)));



}

ui_configuracion::~ui_configuracion()
{
    delete ui;
}

void ui_configuracion::on_pushButton_afiliados_clicked()
{
    QString file1Name = QFileDialog::getOpenFileName(this,
             tr("Abrir CSV Afiliados "), ".", tr("CSV Archivos (*.csv)"));
        ui->label_afiliados->setText(file1Name);
        if(ui->label_afiliados->text().size() > 0)
        {
                ui->pushButton_proc_afil->setEnabled(true);
        }
}

void ui_configuracion::on_pushButton_atenciones_clicked()
{
    QString file1Name = QFileDialog::getOpenFileName(this,
             tr("Abrir CSV Afiliados "), ".", tr("CSV Archivos (*.csv)"));
        ui->label_atenciones->setText(file1Name);
        if(ui->label_atenciones->text().size() > 0)
        {
                ui->pushButton_proc_atenciones->setEnabled(true);
        }
}

void ui_configuracion::procesarAfiliados()
{
    ui->label_messages->setText("Procesando Afiliados");
    QSqlQuery q;
    QString fileName = ui->label_afiliados->text();
    QFile inputFile(fileName);
    QMessageBox msgBox;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       QString line = in.readLine();//INSTRUCCION PARA LEER Y OMITIR LA CABECERAS
       QString query;
       int contador =0;

       while (!in.atEnd())
       {
          qApp->processEvents();
          QStringList wordList;
          line = in.readLine();
          wordList = line.split(';');
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
                  "F_BAJA"
                  ") VALUES('"+wordList.at(0)+"','"+
                  wordList.at(1)+"','"+
                  wordList.at(2)+"','"+
                  wordList.at(3)+"','"+
                  wordList.at(4)+"','"+
                  wordList.at(5)+"','"+
                  wordList.at(6)+"','"+
                  wordList.at(7)+"','"+
                  wordList.at(8)+"','"+
                  wordList.at(9)+"','"+
                  wordList.at(10)+"','"+
                  wordList.at(11)+"')";          

          if(!q.exec(query)){
              msgBox.setText(q.lastError().text());
              msgBox.exec();

          }
          contador+=1;
          ui->label_messages->setText(QString::number(contador));



       }
       inputFile.close();
    }
    else{
        msgBox.setText("No se pudo abrir el archivo ");
        msgBox.exec();
    }

    ui->label_messages->setText("Termino de procesar Afiliados");

}

void ui_configuracion::procesarAtenciones()
{
    ui->label_messages->setText("Procesando Atenciones");
    QSqlQuery q;
    int contador =0;

    QString fileName = ui->label_atenciones->text();
    QFile inputFile(fileName);
    QMessageBox msgBox;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       QString line = in.readLine();//INSTRUCCION PARA LEER Y OMITIR LA CABECERAS
       QString query;

       while (!in.atEnd())
       {
          qApp->processEvents();
          QStringList wordList;
          line = in.readLine();
          wordList = line.split(';');
          contador+=1;


          QString AFIL_DNI = wordList.at(1);
          AFIL_DNI = AFIL_DNI.remove(0,6);
          query = "INSERT OR IGNORE INTO atencion ("
                  "NRO_FORMATO,"
                  "AFIL_DNI,"
                  "FEC_ATENCION,"
                  "EESS,"
                  "SERVICIO,"
                  "CONTRATO,"
                  "TPROFESIONAL,"
                  "PROFESIONAL,"
                  "TARIFA,"
                  "DIAGNOSTICO,"
                  "TIPO_ATENCION,"
                  "FECHA_REGISTRO,"
                  "LUGAR_ATENCION,"
                  "CONVENIO,"
                  "HIS_CLI,"
                  "EESS_REFERENCIA,"
                  "PERIODO,"
                  "CON_MATERNA,"
                  "COMPONENTE,"
                  "TIPO_PAGO,"
                  "EDAD_GESTACIONAL,"
                  "DESTINO,"
                  "FEC_PARTO,"
                  "FEC_PROB_PARTO"
                  ") VALUES('"+wordList.at(0)+"','"+
                  AFIL_DNI+"','"+
                  wordList.at(2)+"','"+
                  wordList.at(7)+"','"+
                  wordList.at(8)+"','"+
                  wordList.at(10)+"','"+
                  wordList.at(11)+"','"+
                  wordList.at(12)+"','"+
                  wordList.at(13)+"','"+
                  wordList.at(14)+"','"+
                  wordList.at(15)+"','"+
                  wordList.at(16)+"','"+
                  wordList.at(17)+"','"+
                  wordList.at(18)+"','"+
                  wordList.at(19)+"','"+
                  wordList.at(21)+"','"+
                  wordList.at(22)+"','"+
                  wordList.at(23)+"','"+
                  wordList.at(24)+"','"+
                  wordList.at(25)+"','"+
                  wordList.at(27)+"','"+
                  wordList.at(28)+"','"+
                  wordList.at(29)+"','"+
                  wordList.at(30)+"')";          



          if(!q.exec(query)){

              msgBox.setText(q.lastError().text());
              msgBox.exec();

          }
          //AGREGANDO PACIENTE
          QString DISA = wordList.at(1);
          DISA = DISA.remove(3,11);
          QString T_AFIL = wordList.at(1);
          T_AFIL = T_AFIL.remove(0,4);
          T_AFIL = T_AFIL.remove(1,9);


          QString F_AFIL= "01/01/2000";
          QString F_BAJA= "00/00/0000";
          QString EESS= wordList.at(7);
          EESS = EESS.remove(0,13);
          QString ETNIA = "80";
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
                  ") VALUES('3300','"+
                  EESS+"','"+
                  DISA+"','"+
                  T_AFIL+"','"+
                  wordList.at(1)+"','"+
                  AFIL_DNI+"','"+
                  F_AFIL+"','"+
                  wordList.at(3)+"','"+
                  wordList.at(6)+"','"+
                  wordList.at(4)+"','"+
                  wordList.at(5)+"','"+
                  F_BAJA+"','"+
                  AFIL_DNI+"','"+
                  ETNIA+"')";


          if(!q.exec(query)){
              msgBox.setText(q.lastError().text());
              msgBox.exec();

          }
          ui->label_messages->setText(QString::number(contador));



       }
       inputFile.close();
       ui->label_messages->setText("Termino de Procesar Atenciones");
    }
    else{
        msgBox.setText("No se pudo abrir el archivo ");
        msgBox.exec();
    }





}

void ui_configuracion::procesarCie()
{
    ui->label_messages->setText("Procesando Cie");
    QSqlQuery q;
    QString fileName = ui->label_cie->text();
    QFile inputFile(fileName);
    QMessageBox msgBox;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       QString line = in.readLine();//INSTRUCCION PARA LEER Y OMITIR LA CABECERAS
       QString query;
       int contador =0;

       while (!in.atEnd())
       {
          qApp->processEvents();
          QStringList wordList;
          line = in.readLine();
          wordList = line.split(';');
          query = "INSERT OR IGNORE INTO cie ("
                  "COD_CAT,"                 
                  "DESC_ENF"
                  ") VALUES('"+wordList.at(0)+wordList.at(1)+"','"+wordList.at(2)+"')";

          if(!q.exec(query)){
              msgBox.setText(q.lastError().text());
              msgBox.exec();
          }
          contador+=1;
          ui->label_messages->setText(QString::number(contador));
       }
       inputFile.close();
    }
    else{
        msgBox.setText("No se pudo abrir el archivo ");
        msgBox.exec();
    }

    ui->label_messages->setText("Termino de procesar cie");

}

void ui_configuracion::crearDB()
{

}

void ui_configuracion::loadMeasurements()
{
    ui->tableWidget_medidas->setItem(0, 0, new QTableWidgetItem("FACTOR_AJUSTE"));
    ui->tableWidget_medidas->setItem(1, 0, new QTableWidgetItem("COD_EESS"));
    ui->tableWidget_medidas->setItem(2, 0, new QTableWidgetItem("NOM_EESS"));
    ui->tableWidget_medidas->setItem(3, 0, new QTableWidgetItem("IPRESS"));
    ui->tableWidget_medidas->setItem(4, 0, new QTableWidgetItem("ITINERANTE"));
    ui->tableWidget_medidas->setItem(5, 0, new QTableWidgetItem("OFERTA"));
    ui->tableWidget_medidas->setItem(6, 0, new QTableWidgetItem("INTRAMURAL"));
    ui->tableWidget_medidas->setItem(7, 0, new QTableWidgetItem("EXTRAMURAL"));
    ui->tableWidget_medidas->setItem(8, 0, new QTableWidgetItem("AMBULATORIA"));
    ui->tableWidget_medidas->setItem(9, 0, new QTableWidgetItem("REFERENCIA"));
    ui->tableWidget_medidas->setItem(10, 0, new QTableWidgetItem("EMERGENCIA"));
    ui->tableWidget_medidas->setItem(11, 0, new QTableWidgetItem("COD_RENAES"));
    ui->tableWidget_medidas->setItem(12, 0, new QTableWidgetItem("NOMBRE_IPRESS"));
    ui->tableWidget_medidas->setItem(13, 0, new QTableWidgetItem("HOJA_REFERENCIA"));
    ui->tableWidget_medidas->setItem(14, 0, new QTableWidgetItem("TDI"));
    ui->tableWidget_medidas->setItem(15, 0, new QTableWidgetItem("DOCUMENTO_IDENTIDAD"));
    ui->tableWidget_medidas->setItem(16, 0, new QTableWidgetItem("DIRESA"));
    ui->tableWidget_medidas->setItem(17, 0, new QTableWidgetItem("NUMERO"));
    ui->tableWidget_medidas->setItem(18, 0, new QTableWidgetItem("INSTITUCION"));
    ui->tableWidget_medidas->setItem(19, 0, new QTableWidgetItem("COD_SEGURO"));
    ui->tableWidget_medidas->setItem(20, 0, new QTableWidgetItem("APELL_PATERNO"));
    ui->tableWidget_medidas->setItem(21, 0, new QTableWidgetItem("APELL_MATERNO"));
    ui->tableWidget_medidas->setItem(22, 0, new QTableWidgetItem("NOMBRES"));
    ui->tableWidget_medidas->setItem(23, 0, new QTableWidgetItem("OTROS_NOMBRES"));
    ui->tableWidget_medidas->setItem(24, 0, new QTableWidgetItem("SEX_M"));
    ui->tableWidget_medidas->setItem(25, 0, new QTableWidgetItem("SEX_F"));
    ui->tableWidget_medidas->setItem(26, 0, new QTableWidgetItem("GESTANTE"));
    ui->tableWidget_medidas->setItem(27, 0, new QTableWidgetItem("PUERPERA"));
    ui->tableWidget_medidas->setItem(28, 0, new QTableWidgetItem("FEC_PARTO"));
    ui->tableWidget_medidas->setItem(29, 0, new QTableWidgetItem("FEC_NACIMIENTO"));
    ui->tableWidget_medidas->setItem(30, 0, new QTableWidgetItem("FEC_FALLECIMIENTO"));
    ui->tableWidget_medidas->setItem(31, 0, new QTableWidgetItem("NUM_HISTORIA"));
    ui->tableWidget_medidas->setItem(32, 0, new QTableWidgetItem("ETNIA"));
    ui->tableWidget_medidas->setItem(33, 0, new QTableWidgetItem("DNI_CNV_AFIL_RN"));
    ui->tableWidget_medidas->setItem(34, 0, new QTableWidgetItem("FEC_ATENCION"));
    ui->tableWidget_medidas->setItem(35, 0, new QTableWidgetItem("COD_PRES"));
    ui->tableWidget_medidas->setItem(36, 0, new QTableWidgetItem("ATE_DIREC"));
    ui->tableWidget_medidas->setItem(37, 0, new QTableWidgetItem("ASEGURADO"));


    ui->tableWidget_medidas->setItem(38, 0, new QTableWidgetItem("COD_RENAES_CONTRAREF"));

    ui->tableWidget_medidas->setItem(39, 0, new QTableWidgetItem("NOMBRE_IPRESS_CONTRAREF"));

    ui->tableWidget_medidas->setItem(40, 0, new QTableWidgetItem("DESCRIPCION1"));

    ui->tableWidget_medidas->setItem(41, 0, new QTableWidgetItem("DESCRIPCION2"));

    ui->tableWidget_medidas->setItem(42, 0, new QTableWidgetItem("DESCRIPCION3"));

    ui->tableWidget_medidas->setItem(43, 0, new QTableWidgetItem("DESCRIPCION4"));

    ui->tableWidget_medidas->setItem(44, 0, new QTableWidgetItem("DESCRIPCION5"));

    ui->tableWidget_medidas->setItem(45, 0, new QTableWidgetItem("PI1"));

    ui->tableWidget_medidas->setItem(46, 0, new QTableWidgetItem("PI2"));

    ui->tableWidget_medidas->setItem(47, 0, new QTableWidgetItem("PI3"));

    ui->tableWidget_medidas->setItem(48, 0, new QTableWidgetItem("PI4"));

    ui->tableWidget_medidas->setItem(49, 0, new QTableWidgetItem("PI5"));

    ui->tableWidget_medidas->setItem(50, 0, new QTableWidgetItem("DI1"));

    ui->tableWidget_medidas->setItem(51, 0, new QTableWidgetItem("DI2"));

    ui->tableWidget_medidas->setItem(52, 0, new QTableWidgetItem("DI3"));

    ui->tableWidget_medidas->setItem(53, 0, new QTableWidgetItem("DI4"));

    ui->tableWidget_medidas->setItem(54, 0, new QTableWidgetItem("DI5"));

    ui->tableWidget_medidas->setItem(55, 0, new QTableWidgetItem("RI1"));

    ui->tableWidget_medidas->setItem(56, 0, new QTableWidgetItem("RI2"));

    ui->tableWidget_medidas->setItem(57, 0, new QTableWidgetItem("RI3"));

    ui->tableWidget_medidas->setItem(58, 0, new QTableWidgetItem("RI4"));

    ui->tableWidget_medidas->setItem(59, 0, new QTableWidgetItem("RI5"));

    ui->tableWidget_medidas->setItem(60, 0, new QTableWidgetItem("DE1"));

    ui->tableWidget_medidas->setItem(61, 0, new QTableWidgetItem("DE2"));

    ui->tableWidget_medidas->setItem(62, 0, new QTableWidgetItem("DE3"));

    ui->tableWidget_medidas->setItem(63, 0, new QTableWidgetItem("DE4"));

    ui->tableWidget_medidas->setItem(64, 0, new QTableWidgetItem("DE5"));

    ui->tableWidget_medidas->setItem(65, 0, new QTableWidgetItem("RE1"));

    ui->tableWidget_medidas->setItem(66, 0, new QTableWidgetItem("RE2"));

    ui->tableWidget_medidas->setItem(67, 0, new QTableWidgetItem("RE3"));

    ui->tableWidget_medidas->setItem(68, 0, new QTableWidgetItem("RE4"));

    ui->tableWidget_medidas->setItem(69, 0, new QTableWidgetItem("RE5"));

    ui->tableWidget_medidas->setItem(70, 0, new QTableWidgetItem("DNI_RESP"));

    ui->tableWidget_medidas->setItem(71, 0, new QTableWidgetItem("NOMBRE_RESP"));

    ui->tableWidget_medidas->setItem(72, 0, new QTableWidgetItem("COLEGIATURA_RESP"));

    ui->tableWidget_medidas->setItem(73, 0, new QTableWidgetItem("CODIGO_RESP"));

    ui->tableWidget_medidas->setItem(74, 0, new QTableWidgetItem("ESPECIALIDAD_RESP"));

    ui->tableWidget_medidas->setItem(75, 0, new QTableWidgetItem("RNE_RESP"));

    ui->tableWidget_medidas->setItem(76, 0, new QTableWidgetItem("EGRESADO_RESP"));

    QSqlQuery query;
    query.prepare("SELECT * FROM medida WHERE ID = '1'");
    query.exec();
    {
        if(query.size()!=0)
        {
            query.first();
            QStringList salida;
            salida= query.value(1).toString().split("-");            
            for(int i=1;i<78;i++){
               salida= query.value(i).toString().split("-");               
               ui->tableWidget_medidas->setItem(i-1, 1, new QTableWidgetItem(salida.at(0)));
               ui->tableWidget_medidas->setItem(i-1, 2, new QTableWidgetItem(salida.at(1)));
            }
        }
    }
}

void ui_configuracion::formatTableWidget()
{
     ui->tableWidget_medidas->setRowCount(38);
     ui->tableWidget_medidas->setColumnCount(3);

     m_TableHeader<<"NOMBRE"<<"HORIZONTAL"<<"VERTICAL";
     ui->tableWidget_medidas->setHorizontalHeaderLabels(m_TableHeader);
     ui->tableWidget_medidas->verticalHeader()->setVisible(true);
     //ui->tableWidget_medidas->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tableWidget_medidas->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableWidget_medidas->setSelectionMode(QAbstractItemView::SingleSelection);
     ui->tableWidget_medidas->setShowGrid(true);
     ui->tableWidget_medidas->setStyleSheet("QTableView {selection-background-color: blue;}");
     //ui->tableWidget_medidas->setGeometry(QApplication::desktop()->screenGeometry());

     //insert data
     /*ui->tableWidget_medidas->setItem(0, 0, new QTableWidgetItem("FACTOR"));
     ui->tableWidget_medidas->setItem(0, 1, new QTableWidgetItem("0.0255345"));
     ui->tableWidget_medidas->setItem(0, 2, new QTableWidgetItem("0.0265454"));*/

     QObject::connect(ui->tableWidget_medidas, SIGNAL( cellDoubleClicked (int, int) ),this, SLOT( cellSelected( int, int ) ) );

}

void ui_configuracion::on_pushButton_proc_afil_clicked()
{
    procesarAfiliados();

}

void ui_configuracion::on_pushButton_proc_atenciones_clicked()
{
    procesarAtenciones();
}

void ui_configuracion::on_pushButton_createdb_clicked()
{
     dbconexion* s = dbconexion::getInstance();
     dbmanager* d = new dbmanager();
     int salida = d->createDB();
     if(salida == -10)
         ui->label_messages->setText("Base de datos creada correctamente");
     else{
         ui->label_messages->setText("Codigo de error: " + QString::number(salida));
     }
}

void ui_configuracion::on_pushButton_exec_query_clicked()
{
    QSqlQuery q;
    if(!q.exec(ui->lineEdit->text()))
    {
        ui->label_messages->setText(q.lastError().text());
    }
    else {
        ui->label_messages->setText(QString::number(q.numRowsAffected()));
    }
}

void ui_configuracion::cellSelected(int nRow, int nCol)
{

}

void ui_configuracion::on_pushButton_guardar_medidas_clicked()
{
    QMessageBox msgBox;
    if(ui->pushButton_guardar_medidas->text() == "Guardar Medidas"){
        QSqlQuery q;
        q.prepare("INSERT OR REPLACE INTO medida("
                       "ID,"
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
                 "EGRESADO_RESP ) VALUES("
                      "1,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                      "?,"
                       "?,"
                       "?,"
                       "?,"
                       "?,"
                       "?,"
                       "?,"
                       "?,"
                       "?,"
                       "?,"
                       "?,"
                       "?,"
                       "?,"
                       "?,"
                       "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"

                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                  "?,"
                      "?)");

        QString medida;
        //VERIFICANDO SI EXISTE TEXTO EN CELDAS
        bool flag = true;

        for(int i=0;i<76;i++){
            if(ui->tableWidget_medidas->item(i,1)->text().size() <=0 || ui->tableWidget_medidas->item(i,2)->text().size() <= 0)
                flag = false;
            else {
                medida = ui->tableWidget_medidas->item(i,1)->text()+"-"+ui->tableWidget_medidas->item(i,2)->text();
                q.bindValue(i,medida);

            }
        }

        if(flag)
        {


            if(!q.exec()){
                msgBox.setText(q.lastError().text());
                msgBox.exec();

            }



        }
        else {
            msgBox.setText("Existen Celdas vacias, Complete cada medida");
            msgBox.exec();

        }
    }
    else{

        loadMeasurements();
        ui->pushButton_guardar_medidas->setText("Guardar Medidas");
    }

}

void ui_configuracion::on_tableWidget_medidas_cellDoubleClicked(int row, int column)
{

}

void ui_configuracion::on_tableWidget_medidas_cellChanged(int row, int column)
{

    //ui->tableWidget_medidas->item(row,column)->setText(ui->tableWidget_medidas->item(row,column)->text());
}

void ui_configuracion::updateMessage(QString msg)
{
    ui->label_messages->setText(msg);
}

void ui_configuracion::on_pushButton_cie_clicked()
{
    QString file1Name = QFileDialog::getOpenFileName(this,
             tr("Abrir CSV CIE10 "), ".", tr("CSV Archivos (*.csv)"));
        ui->label_cie->setText(file1Name);
        if(ui->label_cie->text().size() > 0)
        {
                ui->pushButton_proc_cie->setEnabled(true);
        }

}

void ui_configuracion::on_pushButton_proc_cie_clicked()
{
    procesarCie();
}

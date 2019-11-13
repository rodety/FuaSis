#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbconexion* s = dbconexion::getInstance();
    on_actionFUA_triggered();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFUA_triggered()
{
    bool control = true;
    foreach(QWidget *widget, QApplication::topLevelWidgets()) {


      if(widget->objectName() == "formAtencion")
      {
          setCentralWidget(widget);
          control = false;

      }
    }
    if(control)
    {
        ui_atencion* formAtencion;

        formAtencion=new ui_atencion;
        //formAtencion->setComportamiento(0);
        setCentralWidget(formAtencion);
        this->showMaximized();

    }
}

void MainWindow::on_actionCONFIGURACION_triggered()
{
    bool control = true;
    foreach(QWidget *widget, QApplication::topLevelWidgets()) {


      if(widget->objectName() == "formConfiguracion")
      {
          setCentralWidget(widget);
          control = false;

      }
    }
    if(control)
    {
        ui_configuracion* formConfiguracion;
        formConfiguracion=new ui_configuracion;
        //formAtencion->setComportamiento(0);
        setCentralWidget(formConfiguracion);
        this->showMaximized();

    }
}

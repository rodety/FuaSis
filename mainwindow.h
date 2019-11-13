#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <atencion/ui_atencion.h>
#include <configuracion/ui_configuracion.h>
#include <QDebug>
#include <configuracion/dbconexion.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionFUA_triggered();

    void on_actionCONFIGURACION_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<QAction*> modulos;

};

#endif // MAINWINDOW_H

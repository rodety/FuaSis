#ifndef UI_CONFIGURACION_H
#define UI_CONFIGURACION_H

#include <QWidget>
#include <QMessageBox>
#include <QStringList>
namespace Ui {
class ui_configuracion;
}

class ui_configuracion : public QWidget
{
    Q_OBJECT

public:
    explicit ui_configuracion(QWidget *parent = nullptr);
    ~ui_configuracion();

private slots:
    void on_pushButton_afiliados_clicked();

    void on_pushButton_atenciones_clicked();

    void on_pushButton_proc_afil_clicked();

    void on_pushButton_proc_atenciones_clicked();

    void on_pushButton_createdb_clicked();

    void on_pushButton_exec_query_clicked();

    void cellSelected(int nRow, int nCol);

    void on_pushButton_guardar_medidas_clicked();

    void on_tableWidget_medidas_cellDoubleClicked(int row, int column);

    void on_tableWidget_medidas_cellChanged(int row, int column);
    void updateMessage(QString msg);
    void on_pushButton_cie_clicked();

    void on_pushButton_proc_cie_clicked();

    void on_pushButton_update_db_clicked();

signals:
    void showMessage(QString msg);

private:
    Ui::ui_configuracion *ui;
    void procesarAfiliados();
    void procesarAtenciones();
    void procesarCie();
    void crearDB();
    QStringList m_TableHeader;
    QStringList m_TableRow;
    void loadMeasurements();
    void formatTableWidget();
};

#endif // UI_CONFIGURACION_H

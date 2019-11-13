#ifndef UI_ATENCION_H
#define UI_ATENCION_H

#include <QWidget>
#include <QSqlQueryModel>
class QAbstractItemModel;
class QComboBox;
class QCompleter;
class QLabel;
class QLineEdit;
class QProgressBar;

class TextEdit;


namespace Ui {
class ui_atencion;
}

class ui_atencion : public QWidget
{
    Q_OBJECT

public:
    explicit ui_atencion(QWidget *parent = nullptr);
    ~ui_atencion();

private slots:
    void on_pushButton_guardar_eess_clicked();

    void on_pushButton_buscar_clicked();

    void on_pushButton_search_clicked();

    void on_tableView_result_search_doubleClicked(const QModelIndex &index);

    void on_tableView_result_search_clicked(const QModelIndex &index);

    void on_pushButton_imprimir_clicked();

    void on_lineEdit_doc_identidad_returnPressed();

    void on_lineEdit_search_dni_returnPressed();

    void on_pushButton_nuevo_paciente_clicked();

    void on_pushButton_edit_data_clicked();

    void on_lineEdit_cod_renaes_textEdited(const QString &arg1);

    void on_radioButton_referencia_clicked(bool checked);

    void on_radioButton_referencia_toggled(bool checked);

    void cleanWindow();

    void on_pushButton_guardar_paciente_clicked();

    void on_lineEdit_descripcion1_textEdited(const QString &arg1);

    void on_pushButton_guardar_profesional_clicked();

    void on_finised_editing_completingTextEdit1();

    void on_finised_editing_completingTextCie1();

    void on_finised_editing_completingTextEdit2();

    void on_finised_editing_completingTextCie2();

    void on_finised_editing_completingTextEdit3();

    void on_finised_editing_completingTextCie3();

    void on_finised_editing_completingTextEdit4();

    void on_finised_editing_completingTextCie4();

    void on_finised_editing_completingTextEdit5();

    void on_finised_editing_completingTextCie5();

    void on_finised_editing_completingTextDni_profe();
    void on_finised_editing_completingTextNombre_profe();
    void on_finised_editing_completingTextNro_colegiatura();
    void on_finised_editing_completingTextDoc_identidad();
    void on_pushButton_imprimir_diagnostico_clicked();

    void on_radioButton_clicked(bool checked);

    void on_radioButton_gestante_clicked(bool checked);

    void on_radioButton_puerpera_clicked(bool checked);

    void on_radioButton_femenino_clicked(bool checked);

    void on_radioButton_masulino_clicked(bool checked);

private:
    Ui::ui_atencion *ui;
    void loadDefaultData();
    QSqlQueryModel* buscarPaciente(QString);
    QSqlQueryModel* buscarAtenciones(QString);
    void imprime();
    void separa(QPainter &p, int x, int y, QString text, int factor);
    void separaDate(QPainter &p, int x, int y, QString text, int factor);
    void separaDateYear(QPainter &p, int x, int y, QString text, int factor);
    QHash<int, QString> hash;
    void behaviorReferencia(bool s);
    void behaviorMaterna(bool s);
    QAbstractItemModel *modelFromFile(const QString& fileName);
    QCompleter *completer;
    QCompleter *completer1;
    QCompleter *completer2;
    TextEdit *completingTextEdit1;
    TextEdit *completingTextEdit2;
    TextEdit *completingTextEdit3;
    TextEdit *completingTextEdit4;
    TextEdit *completingTextEdit5;
    TextEdit *completingTextCie1;
    TextEdit *completingTextCie2;
    TextEdit *completingTextCie3;
    TextEdit *completingTextCie4;
    TextEdit *completingTextCie5;
    TextEdit *completingTextDni_profe;
    TextEdit *completingTextNombre_profe;
    TextEdit *completingTextNro_colegiatura;
    TextEdit *completingTextDoc_identidad;

    void createDescripcionCie();
    void createCodCie();
    void createDoc_indetidad();

    void createResponsable();
    void conexionSlot();
    bool activareDni_profe;
    bool activateNombre_profe;
    bool activateNro_colegiatura;

    bool activatedText1;
    bool activatedText2;
    bool activatedText3;
    bool activatedText4;
    bool activatedText5;

    bool activatedCie1;
    bool activatedCie2;
    bool activatedCie3;
    bool activatedCie4;
    bool activatedCie5;

};

#endif // UI_ATENCION_H

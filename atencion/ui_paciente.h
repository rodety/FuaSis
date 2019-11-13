#ifndef UI_PACIENTE_H
#define UI_PACIENTE_H

#include <QWidget>

namespace Ui {
class ui_paciente;
}

class ui_paciente : public QWidget
{
    Q_OBJECT

public:
    explicit ui_paciente(QWidget *parent = nullptr);
    ~ui_paciente();
    void loadDefaultNew();
    void loadDefaultEdit();
    void setDni(QString dni);

private slots:
    void on_pushButton_guardar_clicked();

    void on_pushButton_cancelar_clicked();

private:
    Ui::ui_paciente *ui;
    QString DNI;
    QString comportamiento;

};

#endif // UI_PACIENTE_H

#ifndef DELETE_CONTACT_DIALOG_H
#define DELETE_CONTACT_DIALOG_H
#include <QTableWidget>
#include <QDialog>
#include "adress.h"

namespace Ui {
class delete_contact_dialog;
}

class delete_contact_dialog : public QDialog
{
    Q_OBJECT

public:
    //konstruktør og dekonstruktør
    explicit delete_contact_dialog(QWidget *parent = nullptr);
    ~delete_contact_dialog();

    //deklarerer funksjon for å endre label
    void setObjectContactName(QString name);

private slots:
    //Slot funksjoner for knapper i vindu
    void on_delete_pushButton_clicked();
    void on_cancel_pushButton_clicked();

private:
    Ui::delete_contact_dialog *ui;

    //Deklarerer variabler
    QString objectContactName;
    int contactVectorPos{};

signals:
    //sender signal, brukes i on_delete_oushButton_clicked()
    void sendConfirmDeleteContact(int contactVectorPos);

};

#endif // DELETE_CONTACT_DIALOG_H

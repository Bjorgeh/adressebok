#ifndef UPDATE_CONTACT_DIALOG_H
#define UPDATE_CONTACT_DIALOG_H
#include "adress.h"
#include <QVector>
#include <QDialog>

namespace Ui {
class update_contact_dialog;
}
//lager klassen
class update_contact_dialog : public QDialog
{
    Q_OBJECT

public:
    //konstruktør og dekonstruktør
    explicit update_contact_dialog(QVector<QString> contact,QWidget *parent = nullptr);
    ~update_contact_dialog();

    //deklarerer funksjoner for dataupdate
    QString updateName();
    QString updateAdr();
    QString updatePostal();
    QString updateEmail();
    QString updateNumber();

    //variabel for posisjon i vektor
    int currentVectorPos(int pos);

private slots:
    //Slot funksjoner for knapper i vindu
    void on_update_pushButton_clicked();
    void on_cancel_pushButton_clicked();

private:
    Ui::update_contact_dialog *ui;

    //variabel for posisjon i vektor
    int contactVectorPos{};

signals:
    //signal for å sende oppdatert kontakt til mainwindow
    void sendUpdatedContact(adresses *contact);
};

#endif // UPDATE_CONTACT_DIALOG_H

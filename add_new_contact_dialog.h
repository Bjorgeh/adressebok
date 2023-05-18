#ifndef ADD_NEW_CONTACT_DIALOG_H
#define ADD_NEW_CONTACT_DIALOG_H
#include "adress.h"
#include <QDialog>

namespace Ui {
class add_new_contact_dialog;
}

//lager klassen
class add_new_contact_dialog : public QDialog
{
    Q_OBJECT

public:
    //konstruktør og dekonstruktør
    explicit add_new_contact_dialog(QWidget *parent = nullptr);
    ~add_new_contact_dialog();

private slots:
    //Deklarerer slot funksjoner for vinduet
    void on_pushButton_add_new_clicked();
    void on_pushButton_2_exit_add_new_clicked();

private:
    Ui::add_new_contact_dialog *ui;

signals:
    //brukes med emit signal i definasjon av 'on_pushButton_add_new_clicked()'
    void sendNewContact(adresses * addr);
};

#endif // ADD_NEW_CONTACT_DIALOG_H

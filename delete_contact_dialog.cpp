#include "delete_contact_dialog.h"
#include "add_new_contact_dialog.h"
#include "ui_delete_contact_dialog.h"

//konstruktør
delete_contact_dialog::delete_contact_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_contact_dialog)
{
    ui->setupUi(this);
}
//dekonstruktør
delete_contact_dialog::~delete_contact_dialog()
{
    delete ui;
}

//Endrer lagel til kontaktnavn
void delete_contact_dialog::setObjectContactName(QString name)
{
    ui->name_label->setText(name);
}

//Lukker vindu
void delete_contact_dialog::on_cancel_pushButton_clicked()
{
    this->close();
}

//emitter signal og lukker vindu
void delete_contact_dialog::on_delete_pushButton_clicked()
{
    emit sendConfirmDeleteContact(contactVectorPos);
    this->close();
}




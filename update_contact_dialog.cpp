#include "update_contact_dialog.h"
#include "ui_update_contact_dialog.h"

//konstruktør mottar ekstra: database vektor
update_contact_dialog::update_contact_dialog(QVector<QString> contact,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::update_contact_dialog)
{
    //Lager variabler for info i vektor
    QString name = contact.at(0);
    QString adr = contact.at(1);
    QString postal = contact.at(2);
    QString email = contact.at(3);
    QString number = contact.at(4);

    ui->setupUi(this);
    //Setter placeholder text til nåværende info
    ui->update_name->setPlaceholderText(name);
    ui->update_address->setPlaceholderText(adr);
    ui->update_postal->setPlaceholderText(postal);
    ui->update_email->setPlaceholderText(email);
    ui->update_number->setPlaceholderText(number);
}

//dekonstruktør
update_contact_dialog::~update_contact_dialog()
{
    delete ui;
}

//Hvis input info ikke er oppdatert eller tom, returneres opprinnelig info
//Er info oppdatert returneres oppdatert info
QString update_contact_dialog::updateName()
{
    if(ui->update_name->text() == ""){
        return ui->update_name->placeholderText();
    }
    else{return ui->update_name->text();};
}

QString update_contact_dialog::updateAdr()
{
    if(ui->update_address->text() == ""){
        return ui->update_address->placeholderText();
    }
    else{return ui->update_address->text();};
}

QString update_contact_dialog::updatePostal()
{
    if(ui->update_postal->text() == ""){
        return ui->update_postal->placeholderText();
    }
    else{return ui->update_postal->text();};
}

QString update_contact_dialog::updateEmail()
{
    if(ui->update_email->text() == ""){
        return ui->update_email->placeholderText();
    }
    else{return ui->update_email->text();};
}

QString update_contact_dialog::updateNumber()
{
    if(ui->update_number->text() == ""){
        return ui->update_number->placeholderText();
    }
    else{return ui->update_number->text();};
}

int update_contact_dialog::currentVectorPos(int pos)
{
     contactVectorPos= pos;
     return pos;
}

//Lukker vindu
void update_contact_dialog::on_cancel_pushButton_clicked()
{
    this->close();
}

//lager nytt adresses ogjekt og sender kontakt til mainwindow
void update_contact_dialog::on_update_pushButton_clicked()
{    
    auto adrre = new adresses(updateName(),updateAdr(),updatePostal(),updateEmail(),updateNumber());   
    emit sendUpdatedContact(adrre);
    this->close();
}

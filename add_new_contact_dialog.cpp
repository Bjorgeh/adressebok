#include "add_new_contact_dialog.h"
#include "qmainwindow.h"
#include "ui_add_new_contact_dialog.h"

//konstruktør
add_new_contact_dialog::add_new_contact_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_new_contact_dialog)
{
    //Starter ui
    ui->setupUi(this);
    this->setWindowTitle(tr("Add contact"));
}

//Dekonstruktør
add_new_contact_dialog::~add_new_contact_dialog()
{
    delete ui;
}

//Når knapp trykkes lager den en ny kontakt av info i linjene
void add_new_contact_dialog::on_pushButton_add_new_clicked()
{
    QString name = ui->name_new->displayText();
    QString address = ui->adress_new->text();
    QString postnr = ui->postnumber_new->text();
    QString email = ui->email_new->text();
    QString phone = ui->phone_new->text();
    //qInfo() << "New info added.";

    //Legger til ny adresseobjekt i vektor.
    adresses *newContact = new adresses(name,address,postnr,email,phone);

    //Testobjekt
    //adresses *newContact = new adresses("n","a","p","e","t");

    //adressebok.push_back(newContact);

    //Sender ny kontakt til mainwindow 'void addContact(adresses* contact);'
    emit sendNewContact(newContact);

    //Lukker vinduet
    this->close();
}

//lukker vindu når knappen trykkes.
void add_new_contact_dialog::on_pushButton_2_exit_add_new_clicked()
{
    this->close();
    //qInfo() << "popup closed";
}


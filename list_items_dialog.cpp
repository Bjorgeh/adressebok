#include "list_items_dialog.h"
#include "ui_list_items_dialog.h"
#include <QListWidgetItem>
#include "adress.h"

//konstruktør mottar ekstra : vektor for bruk i klassen
list_items_Dialog::list_items_Dialog(QVector<adresses*>contactList,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::list_items_Dialog)
{
    ui->setupUi(this);
    //Endrer tittel på vindu
    this->setWindowTitle("Contact List");

    //Mellomlagrer mottatt vektor for ordens skyld
    adressebok_new_copy = contactList;

    //looper gjennom vektoren og viser navn og telefonnummer i listwidget
    for(int i{};i<adressebok_new_copy.size();i++)
    {
        ui->listWidget->addItem(adressebok_new_copy.at(i)->getName() + " : " + adressebok_new_copy.at(i)->getNumber());
    };
}

//dekonstruktør
list_items_Dialog::~list_items_Dialog()
{
    delete ui;
}

//Lukker vinduet
void list_items_Dialog::on_close_pushButton_clicked()
{
    this->close();
}



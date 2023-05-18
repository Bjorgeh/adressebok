#include "help_dialog.h"
#include "ui_help_dialog.h"

//konstruktør
help_Dialog::help_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help_Dialog)
{
    ui->setupUi(this);
}
//Dekonstruktør
help_Dialog::~help_Dialog()
{
    delete ui;
}

//Lukker vindu
void help_Dialog::on_OK_pushButton_clicked()
{
    this->close();
}


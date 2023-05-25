#include "load_from_file_dialog.h"
#include "ui_load_from_file_dialog.h"
// k
load_from_file_Dialog::load_from_file_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::load_from_file_Dialog)
{
    //Setter opp vidnuet, endrer navn, disabler knapp..
    ui->setupUi(this);
    ui->pushButton->setDisabled(true);
    ui->lineEdit->setPlaceholderText(tr("Filename"));
    this->setWindowTitle("Load from file");
}
// ~
load_from_file_Dialog::~load_from_file_Dialog()
{
    delete ui;
}

//Lukker vindu når knanpp trykkes
void load_from_file_Dialog::on_pushButton_2_clicked()
{
    this->close();
}

void load_from_file_Dialog::on_pushButton_3_clicked()
{
    //Åpner browse vindu for å velge fil
    path = QFileDialog::getOpenFileName(this, tr("Open json file"));
    //Lager QFile av filen med path
    QFile file(path);
    //Lager fileinfo objekt for å få bare filnavnet
    QFileInfo *fileInfo = new QFileInfo(path);
    QString fileName = fileInfo->fileName();

    //Hvis fil ikke kan leses viser error
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("File error"), file.errorString());
        return;
    }
    //Setter text i line edit til bare filnavnet
    ui->lineEdit->setPlaceholderText(fileName);

    //Sjekker om .json finnes i filnavnet
    if(fileName.contains(".json"))
        {
            qInfo() << tr("json file found");
            //aktiverer add knapp
            ui->pushButton->setDisabled(false);
        }
}

//Sender path fil mainwindow og lukker vindu
void load_from_file_Dialog::on_pushButton_clicked()
{
    emit filePathSignal(path);
    this->close();
}


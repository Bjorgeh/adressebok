#include "load_from_file_dialog.h"
#include "ui_load_from_file_dialog.h"

load_from_file_Dialog::load_from_file_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::load_from_file_Dialog)
{
    ui->setupUi(this);
    ui->pushButton->setDisabled(true);
    ui->lineEdit->setPlaceholderText(tr("Filename"));
}

load_from_file_Dialog::~load_from_file_Dialog()
{
    delete ui;
}

void load_from_file_Dialog::on_pushButton_2_clicked()
{
    this->close();
}

void load_from_file_Dialog::on_pushButton_3_clicked()
{
    path = QFileDialog::getOpenFileName(this, tr("Open a file"));
    QFile file(path);
    QFileInfo *fileInfo = new QFileInfo(path);
    QString fileName = fileInfo->fileName();

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error"), file.errorString());
        return;
    }
    ui->lineEdit->setPlaceholderText(fileName);

    if(fileName.contains(".json"))
        {
            qInfo() << tr("json file found");
            ui->pushButton->setDisabled(false);
        }
}


void load_from_file_Dialog::on_pushButton_clicked()
{
    emit filePathSignal(path);
    this->close();
}


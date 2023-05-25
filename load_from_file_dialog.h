#ifndef LOAD_FROM_FILE_DIALOG_H
#define LOAD_FROM_FILE_DIALOG_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

namespace Ui {
class load_from_file_Dialog;
}

//Lager klassen
class load_from_file_Dialog : public QDialog
{
    Q_OBJECT

public:
    //konstruktør & dekonstruktør
    explicit load_from_file_Dialog(QWidget *parent = nullptr);
    ~load_from_file_Dialog();

private slots:
    //deklarerer slot funksjoner
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();

private:
    Ui::load_from_file_Dialog *ui;
    //string for path fil json fil
    QString path;

signals:
    //sender signal med path til mainwindow
    QString filePathSignal(QString path);
};

#endif // LOAD_FROM_FILE_DIALOG_H

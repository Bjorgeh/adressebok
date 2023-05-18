#ifndef LIST_ITEMS_DIALOG_H
#define LIST_ITEMS_DIALOG_H
#include "adress.h"
#include <QListWidget>
#include <QDialog>

namespace Ui {
class list_items_Dialog;
}

class list_items_Dialog : public QDialog
{
    Q_OBJECT

public:
    //konstruktør og dekonstruktør
    explicit list_items_Dialog(QVector<adresses*>contactList,QWidget *parent = nullptr);
    ~list_items_Dialog();

private slots:
    //slot funksjon for close knapp
    void on_close_pushButton_clicked();

private:
    Ui::list_items_Dialog *ui;

    //mellomlagrer databasevektor for bruk i klassen
    QVector<adresses*> adressebok_new_copy;

};

#endif // LIST_ITEMS_DIALOG_H

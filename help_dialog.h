#ifndef HELP_DIALOG_H
#define HELP_DIALOG_H

#include <QDialog>

namespace Ui {
class help_Dialog;
}

class help_Dialog : public QDialog
{
    Q_OBJECT

public:
    //konstruktør og dekonstruktør
    explicit help_Dialog(QWidget *parent = nullptr);
    ~help_Dialog();

private slots:
    //deklarerer slot funksjon for ok knappen.
    void on_OK_pushButton_clicked();

private:
    Ui::help_Dialog *ui;
};

#endif // HELP_DIALOG_H

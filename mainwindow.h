#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "adress.h"
#include <QMainWindow>
#include <QAction>
#include <QTableWidget>
#include <QListWidget>
#include <QSettings>
#include <QIODevice>
#include "add_new_contact_dialog.h"
#include "delete_contact_dialog.h"
#include "qstatusbar.h"
#include "update_contact_dialog.h"
#include "help_dialog.h"
#include "list_items_dialog.h"
#include "jsonhandler.h"
#include "load_from_file_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //konstruktør og destruktør
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    //deklarerer funksjoner til vinduer
    void addNew_popup();
    void delete_popup();
    void update_popup();
    void list_popup();
    void help_popup();
    void load_popup();

    //deklarerer funksjoner som tar mot info uten fra klassen
    void addContact(adresses* contact);
    void deleteContact(int pos);
    void updateContact(adresses* contact);

    //deklarerer funksjon for oppdatering av statusbar
    void updateStatusBar(QString message);

    //deklarerer funksjon for file loading
    QString loadFromFile(QString path);

private:
    //ui obj
    Ui::MainWindow *ui;

    //deklarerer funksjoner innen klassen
    void setupActions();
    void setupMenu();
    void setupTable();
    void setupToolBar();

    //deklarerer actions for top tool bar
    QAction* newAct;
    QAction* deleteAct;
    QAction* updateAct;
    QAction* listAct;
    QAction* helpAct;
    QAction* showToolBar;
    QAction* loadAct;

    //Deklarerer variabel for nåværende markerte kontakt
    int currentMarked{};

    //Database vektor
    QVector<adresses*> adressebok_new;

    //Selve widget for å vise kontakter
    QTableWidget *adressListView = new QTableWidget(this);

    //statusbar objekt
    QStatusBar *statusbar = new QStatusBar;

    QToolBar *toolbar;

    //settings med funksjoner for å lagre instillinger og databasevektor
    QSettings *settings;
    void saveSettings();
    void loadSettings();

    //objekt for handling av json data
    jsonHandler *jsonDB = new jsonHandler;


    //test
    QString testText{};

};

#endif // MAINWINDOW_H

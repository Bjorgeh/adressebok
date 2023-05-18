#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "adress.h"
#include <QListWidget>
#include <QTableWidget>
#include <QObject>
#include <QAction>
#include <QMessageBox>
#include <QToolBar>

//konstruktør
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Kjører funksjoner for oppstart av programmet.
    setupActions();
    setupMenu();
    loadSettings();
    setupTable();
    //setupToolBar(true);
    //updateStatusBar("test");
}

//Lagrer kontakter og sletter ui obj
MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

//definerer actions for top meny
void MainWindow::setupActions()
{
    //Setter navn og key shortcuts
    newAct = new QAction(tr("New"),this);
    newAct->setShortcut(QKeySequence::New);

    deleteAct = new QAction(tr("Delete"),this);
    deleteAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));

    updateAct = new QAction(tr("update"),this);
    updateAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_U));

    listAct = new QAction(tr("List"),this);
    listAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));

    helpAct = new QAction(tr("Help"),this);
    helpAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_H));

    showToolBar = new QAction(tr("Show"),this);
    showToolBar->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_T));
    showToolBar->setCheckable(true);

    //'new' starter funksjonen addNew_popup
    connect(newAct, &QAction::triggered,this,&MainWindow::addNew_popup);
    //"delete" starter funksjonen delete_popup
    connect(deleteAct, &QAction::triggered,this,&MainWindow::delete_popup);
    //"update" starter funksjonen update_popup
    connect(updateAct,&QAction::triggered,this,&MainWindow::update_popup);
    //"list" starter funksjonen viewItems
    connect(listAct,&QAction::triggered,this,&MainWindow::list_popup);
    //"help" starter funksjonen help
    connect(helpAct,&QAction::triggered,this,&MainWindow::help_popup);
    //"Show toolbar" starter funksjonen setuptoolbar
    connect(showToolBar,&QAction::triggered,this,&MainWindow::setupToolBar);
}

//setter opp selve menybaren og kobler til actions
void MainWindow::setupMenu()
{
    //Setter opp valgmeny top
    const auto menuFile = menuBar()->addMenu(tr("&File"));
    const auto menuEdit= menuBar()->addMenu(tr("&Edit"));
    const auto menuView = menuBar()->addMenu(tr("&View"));
    const auto menuHelp = menuBar()->addMenu(tr("&Help"));
    const auto showTB = menuBar()->addMenu(tr("&Toolbar"));

    //Legger til actions fra mainwindow klassens private
    menuFile->addAction(newAct);
    menuEdit->addAction(deleteAct);
    menuEdit->addAction(updateAct);
    menuView->addAction(listAct);
    menuHelp->addAction(helpAct);
    showTB->addAction(showToolBar);
}

//Setter opp QTableWidget
void MainWindow::setupTable()
{
    //Rader og kolonner
    adressListView->setColumnCount(5);
    adressListView->setRowCount(adressebok_new.size());

    //Setter som central widget
    this->setCentralWidget(adressListView);

    //setter fast header på toppen av tablet.
    const QStringList headers{tr("Name"),tr("Address"),tr("Postal"),tr("Email"),tr("Number")};
    adressListView->setHorizontalHeaderLabels(headers);

    if(adressebok_new.size() >= 1){
        adressListView->setCurrentCell(0,0);
        //qInfo() << "Selected 0,0";
    };

    //Variabler for palssering i table
    int row{0};
    int column = 0;

    //Loopen henter objekter fra database-vektoren.
    for(int addresseObjekt{0};addresseObjekt<adressebok_new.size();addresseObjekt++){
        auto objektInfoVektor = adressebok_new.at(addresseObjekt)->getViewList();

        //Henter ut info fra objekt-vektor og Lager et QTableWidgetItem av hvert item i vektoren
        for(int objektItem{0};objektItem<objektInfoVektor.size();objektItem++){

                QString item = objektInfoVektor.at(objektItem);
                //qInfo() << item;
                QTableWidgetItem *newItem = new QTableWidgetItem(item);

                //QTableWidgetItem Settes inn i QTableWidget
                adressListView->setItem(row, column, newItem);

                column++;
                if(column>=5){column=0;};
        };

        row++;
    };

    //Endrer statusbar
    updateStatusBar(tr("Contacts: ")+QString::number(adressebok_new.size()));
}

//Setter opp toolbar
void MainWindow::setupToolBar()
{

    //Hvis show toolbar er markert, vises toolbar, ellers slettes objektet.
    if(showToolBar->isChecked()){

        //Lager toolbar objekt
        toolbar = new QToolBar(this);
        //Setter funksjoner og ikoner i toolbaren
        const auto addnew = toolbar->addAction(tr("New"),this, SLOT(addNew_popup()));
        addnew->setIcon(QIcon(":/icons/functionImages/icons/add.png"));

        const auto updatecontact = toolbar->addAction(tr("Update"),this, SLOT(update_popup()));
        updatecontact->setIcon(QIcon(":/icons/functionImages/icons/update.png"));

        const auto deletecontact = toolbar->addAction(tr("Delete"),this, SLOT(delete_popup()));
        deletecontact->setIcon(QIcon(":/icons/functionImages/icons/delete.png"));

        const auto listcontact = toolbar->addAction(tr("List"),this, SLOT(list_popup()));
        listcontact->setIcon(QIcon(":/icons/functionImages/icons/list.png"));

        const auto browsehelp = toolbar->addAction(tr("Help"),this, SLOT(help_popup()));
        browsehelp->setIcon(QIcon(":/icons/functionImages/icons/help.png"));

        //Legger til toolbaren
        addToolBar(Qt::ToolBarArea::LeftToolBarArea,toolbar);
    }

    //sletter toolbar
    else{delete toolbar;};
}

//Lagrer kontakter
void MainWindow::saveSettings()
{
    //Fjerner først gammel info
    settings->clear();

    //Henter objektene i database-vektoren
    for(int i{}; i < adressebok_new.size();i++)
    {
        //Hvis databasen ikke er tom, lagres kontakter med key (string av i) og value (info fra obj)
        if(adressebok_new.isEmpty() == 0){
            QString i_int = QString::number(i);

            //lagrer info i en QList
            QList test{
                        adressebok_new.at(i)->getName(),
                        adressebok_new.at(i)->getAdress(),
                        adressebok_new.at(i)->getPostNr(),
                        adressebok_new.at(i)->getEmail(),
                        adressebok_new.at(i)->getNumber()
            };
            //lagrer qlister med string-nummerert key
            settings->setValue(i_int,test);
        }
    }
}

//Laster inn kontakter
void MainWindow::loadSettings()
{
    settings = new QSettings("Asgeir", "Adressebok");
    int numberOfKeys = settings->allKeys().size();
    //qInfo() << numberOfKeys;
    //qInfo() << settings->allKeys();

    //clearer database-vektoren for ordens skyld
    adressebok_new.clear();

    //Henter info fra Qlistene og lager nye objekter for å lagre i database-vektoren
    for(int i = 0; i < numberOfKeys; i++)
    {
        QString key = QString::number(i);
        QList<QVariant> qlist = settings->value(key).toList();

        //Hvis qlisten ikke er tom
        if (!qlist.isEmpty())
        {
            //Henter ut verdiene fra qlisten
            QString name = qlist[0].toString();
            QString address = qlist[1].toString();
            QString postNr = qlist[2].toString();
            QString email = qlist[3].toString();
            QString number = qlist[4].toString();

            //Lager et nytt adresses objekt og legg det til i database-vektoren
            adresses *adressebok = new adresses(name, address, postNr, email, number);
            adressebok_new.append(adressebok);
        }
    }
}

    //Åpner vindu for å legge til kontakter
void MainWindow::addNew_popup()
{
    updateStatusBar(tr("Adding contact..."));
    //qInfo()<<"Popup";
    add_new_contact_dialog popup;
    //tar imot emit signalet fra add_new_contact_dialog
    connect(&popup,&add_new_contact_dialog::sendNewContact,this,&MainWindow::addContact);
    popup.exec();
    setupTable();
}

    //lager nytt vindu for å slette kontakter
void MainWindow::delete_popup()
{
    updateStatusBar(tr("Deleting contact..."));
    delete_contact_dialog popup;
    connect(&popup,&delete_contact_dialog::sendConfirmDeleteContact,this,&MainWindow::deleteContact);

    if(adressebok_new.size() >= 1) {

        //Sjekker om noen items er markert.
        if(!adressListView->selectedItems().isEmpty()) {

            //Henter markert info fra QTableWidget
            auto markedContactPos = adressListView->selectedItems().at(0)->row();
            auto markedObject = adressebok_new.at(markedContactPos);
            auto markedContactName = markedObject->getName();

            //Sender navn til kontakt til nytt vindu
            popup.setObjectContactName(markedContactName);
            popup.exec();

        }
        else {
            //Viser feilmelding i nytt vindu hvis ingen er markert
            QMessageBox *noMarked = new QMessageBox;
            noMarked->warning(this, tr("No marked contact"),tr("Mark a contact to continue."));
            delete noMarked;
        }
    }
    setupTable();

    //Viser feilmelding hvis ingen kontakter finnes
    if(adressebok_new.size() == 0){
        QMessageBox *noContact = new QMessageBox;
        noContact->warning(this,tr("No contacts found"),tr("Contact list is empty.."));
        delete noContact;
    };

}

    //åpner vindu for å oppdatere kontakter.
void MainWindow::update_popup()
{
    //Endrer statusbar
    updateStatusBar(tr("Updating contact..."));

    //Sjekker om noen items er markert.
    if(!adressListView->selectedItems().isEmpty()) {

        //Henter markert info fra QTableWidget
        auto markedContactPos = adressListView->selectedItems().at(0)->row();
        //auto markedContactPos_col = adressListView->selectedItems().at(0)->column();
        auto markedObject = adressebok_new.at(markedContactPos);

        currentMarked = markedContactPos;
        //Starter ny dialog og sender vector til konstruktør.
        update_contact_dialog *popup = new update_contact_dialog(markedObject->getViewList());

        connect(popup,&update_contact_dialog::sendUpdatedContact,this,&MainWindow::updateContact);

        //Sender posisjon til objekt til update klasse
        popup->currentVectorPos(markedContactPos);
        popup->exec();

        setupTable();
        delete popup;
    }

    else {
        //Viser feilmelding hvis ingen er markert
        QMessageBox *noMarked = new QMessageBox;
        noMarked->warning(this, tr("No marked contact"),tr("Mark a contact to continue."));
        delete noMarked;
    }
}

//Lager nytt vindu og lister opp alle kontaktene
void MainWindow::list_popup()
{
    updateStatusBar(tr("Showing list..."));
    //qInfo() << listUi;
    list_items_Dialog *popup = new list_items_Dialog(adressebok_new);
    popup->exec();
    delete popup;
    setupTable();
}

//Lager nytt vindu for help info
void MainWindow::help_popup()
{ 
    updateStatusBar(tr("Browsing help..."));
    help_Dialog *popup = new help_Dialog;
    popup->exec();

    delete popup;
}

//Slette valgde kontakter
void MainWindow::deleteContact(int pos)
{
    //Markert kontakt
    pos = adressListView->selectedItems().at(0)->row();
    //Gjør om til string for å sammenligne key value
    QString key = QString::number(pos);
    if(pos == 0)
    {
        adressebok_new.pop_front();
        // Oppdater QSettings ved å fjerne den tilsvarende nøkkelen
        settings->remove(key);
    }
    else{adressebok_new.erase(adressebok_new.begin()+pos);settings->remove(key);}
}

//Oppdaterer kontakter
void MainWindow::updateContact(adresses *contact)
{
    for(int i{};i<adressebok_new.size();i++){
        if(adressebok_new.at(i) == adressebok_new.at(currentMarked))
        {
            adressebok_new.replace(i,contact);
            break;
        }
        else{qInfo()<<"updateContact()";}
    }
}

void MainWindow::updateStatusBar(QString message)
{
    ui->statusbar->showMessage(message,0);
    ui->statusbar->show();
}

//Tar mot og legger til kontakt
void MainWindow::addContact(adresses *contact)
{
    adressebok_new.push_back(contact);
    //qInfo() << adressebok_new.at(0);
}

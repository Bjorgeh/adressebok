#ifndef ADRESS_H
#define ADRESS_H
#include <QString>
#include <QVector>


class adresses
{

public:
    //konstruktør og dekonstruktør
    adresses(QString na, QString ad,QString po,QString ema, QString num);
    ~adresses();

    //Deklarerer funksjoner for returnering av info
    QString getName();
    QString getAdress();
    QString getPostNr();
    QString getEmail();
    QString getNumber();

    //deklarerer vektor for retur av all info.
    QVector<QString> getViewList();

    //Deklarerer funksjoner for å sette info
    QString setName(QString na);
    QString setAdress(QString adr);
    QString setPostnr(QString po);
    QString setEmail(QString em);
    QString setNumber(QString num);

private:
    //deklarerer variabler
    QString name{"NoName"};
    QString adress{"NoAddr"};
    QString postnr{"NoPostNr"};
    QString email{"NoMail"};
    QString number{"NoNum"};
    //...vektor
    QVector<QString> viewList;
};

#endif // ADRESS_H

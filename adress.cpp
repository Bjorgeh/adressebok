#include "adress.h"

//konstruktøren setter ny info til variabler og vektor
adresses:: adresses(QString na, QString ad,QString po,QString ema, QString num)
{
    name = na;
    adress = ad;
    number = num;
    email = ema;
    postnr = po;
    viewList = {getName(),getAdress(),getPostNr(),getEmail(),getNumber()};
}

//funksjoner returnerer forskjellig info
QString adresses::getName()
{
    return name;
}

QString adresses::getAdress()
{
    return adress;
}

QString adresses::getPostNr()
{
    return postnr;
}

QString adresses::getEmail()
{
    return email;
}

QString adresses::getNumber()
{
    return number;
}

QVector<QString> adresses::getViewList()
{
    return viewList;
}

adresses::~adresses()
{

}

//setter info og returnerer beskjed om initialisert
QString adresses::setName(QString na)
{
    name = na;
    return "Name changed.";
}

QString adresses::setAdress(QString adr)
{
    adress = adr;
    return "Address changed.";
}

QString adresses::setPostnr(QString po)
{
    postnr = po;
    return "Postal number changed.";
}

QString adresses::setEmail(QString em)
{
    email = em;
    return "Email changed.";
}

QString adresses::setNumber(QString num)
{
    number = num;
    return "Number changed.";
}


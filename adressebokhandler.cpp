#include "adressebokhandler.h"


adressebokHandler::adressebokHandler(QObject *parent) : QObject(parent)
{
}

QVector<adresses *> adressebokHandler::getAdressebok() const
{
    return adressebok;
}

void adressebokHandler::addContact(adresses *contact)
{
    adressebok.push_back(contact);
    emit contactAdded(contact);
}

void adressebokHandler::deleteContact(int index)
{
    if (index >= 0 && index < adressebok.size()) {
        adresses *contact = adressebok.at(index);
        adressebok.remove(index);
        emit contactDeleted(index);
        delete contact;
    }
}

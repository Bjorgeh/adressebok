#ifndef ADRESSEBOKHANDLER_H
#define ADRESSEBOKHANDLER_H

#include <QObject>
#include <QVector>
#include "adress.h"

class adressebokHandler : public QObject
{

public:
    explicit adressebokHandler(QObject *parent = nullptr);

    QVector<adresses *> getAdressebok() const;

public slots:
    void addContact(adresses *contact);
    void deleteContact(int index);

signals:
    void contactAdded(adresses *contact);
    void contactDeleted(int index);

private:
    QVector<adresses *> adressebok;

};

#endif // ADRESSEBOKHANDLER_H

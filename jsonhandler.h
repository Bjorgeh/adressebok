#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "adress.h"


class jsonHandler
{
public:
    jsonHandler();
    ~jsonHandler();

private:
    void saveToJson(QVector<adresses> dataBaseVector);
    void deleteFromJsonFile(int vectorPos);

signals:
    void fileCreated(QString fileName);
    void savedToFile(QString contactName);
    void deletedFromFile(QString contactName);
};

#endif // JSONHANDLER_H

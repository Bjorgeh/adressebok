#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "adress.h"
#include <QCoreApplication>

class jsonHandler
{
public:
    jsonHandler();
    ~jsonHandler();
    void saveToJson(QVector<adresses*> dataBaseVector);
    QVector<adresses*> loadFromJson(QString fileName);
};

#endif // JSONHANDLER_H

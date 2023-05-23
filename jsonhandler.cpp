#include "jsonhandler.h"

jsonHandler::jsonHandler()
{
    //sjekker om jsonfil finnes, hvis ikke lages den. og signal emit fileExists(true) sendes.

    QFile file("dataBase.json");
    bool Exists = file.exists();
    if (!Exists) {
        //lager json objekt
        QJsonObject jsonObject;

        //lager json fil fra objektet
        QJsonDocument jsonDoc(jsonObject);

        //lager JSON-dokumentet til JSON-streng
        QByteArray jsonData = jsonDoc.toJson();

        //Angir filnavnet og åpner filen for skriving
        QString filename = "dataBase.json";
        QFile file(filename);

        if (file.open(QIODevice::WriteOnly))
        {
            // Skriver json string til filen
            file.write(jsonData);
            file.close();

            QString currentPath = QCoreApplication::applicationDirPath();
            qInfo() << "Current working directory: " << currentPath;
            qInfo() << "json fil created: " << filename;
        }
    }
    else{
        QString currentPath = QCoreApplication::applicationDirPath();
        qInfo() << "Current working directory: " << currentPath;
        qInfo() << "json file ready.";
    }
}

void jsonHandler::saveToJson(QVector<adresses*> dataBaseVector)
{
    //tar info fra vektor og skriver det inn i jsonfilen

    QJsonArray jsonArray;
    for (int i{0};i<dataBaseVector.size();i++) {

        //Lager json objekt
        QJsonObject jsonObject;

        jsonObject["name"] = dataBaseVector.at(i)->getName();
        jsonObject["address"] = dataBaseVector.at(i)->getAdress();
        jsonObject["postal"] = dataBaseVector.at(i)->getPostNr();
        jsonObject["email"] = dataBaseVector.at(i)->getEmail();
        jsonObject["number"] = dataBaseVector.at(i)->getNumber();

        //Legger til objekt i array
        jsonArray.append(jsonObject);
    }

    //Skriver til filen
    QJsonDocument jsonDoc(jsonArray);
    QFile file("dataBase.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson());
        file.close();
    }
}

QVector<adresses*> jsonHandler::loadFromJson(QString fileName)
{
    QVector<adresses*> arrayFromJson;
    //sletter objekt fra jsonfil ved hjelp av elements posisjon i vektor

    QFile file(fileName);
    if (file.exists()) {
        if (file.open(QIODevice::ReadWrite)) {
            QByteArray jsonData = file.readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
            QJsonArray jsonArray = jsonDoc.array();
            for(int i{0}; i < jsonArray.size(); i++)
            {
                adresses *tempContact = new adresses("","","","","");
                tempContact->setName(jsonArray.at(i)["name"].toString());
                tempContact->setAdress(jsonArray.at(i)["address"].toString());
                tempContact->setPostnr(jsonArray.at(i)["postal"].toString());
                tempContact->setEmail(jsonArray.at(i)["email"].toString());
                tempContact->setNumber(jsonArray.at(i)["number"].toString());

                arrayFromJson.push_back(tempContact);
            }
            file.close();
        }
        /* //Skriver ut info fra arrayFromJson - test
          for(int i{}; i < arrayFromJson.size(); i++){
            qInfo() << arrayFromJson.at(i)->getName()
                    << arrayFromJson.at(i)->getAdress()
                    << arrayFromJson.at(i)->getPostNr()
                    << arrayFromJson.at(i)->getEmail()
                    << arrayFromJson.at(i)->getNumber();
                }
                */
     return arrayFromJson;
    }
    else{return arrayFromJson;}
}

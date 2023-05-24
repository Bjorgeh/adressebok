#include "jsonhandler.h"

//Konstruktør sjekker om jsonfil finnes, hvis ikke lages den. og signal emit fileExists(true) sendes.
jsonHandler::jsonHandler()
{
    QFile file("dataBase.json");
    bool Exists = file.exists();
    if (!Exists) {
        //lager json objekt
        QJsonObject jsonObject;

        //lager jsondoc objekt fra jsonobjektet
        QJsonDocument jsonDoc(jsonObject);

        //lager JSON-dokumentet til JSON-streng
        QByteArray jsonData = jsonDoc.toJson();

        //Angir filnavnet og åpner filen for skriving
        QString filename = "dataBase.json";
        QFile file(filename);

        //Kjører filen med write only og skriver string til filen
        if (file.open(QIODevice::WriteOnly))
        {
            // Skriver json string til filen
            file.write(jsonData);
            file.close();

            //Henter directory til hvor filen blir lagret
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

//tar info fra databasevektor og skriver det inn i jsonfilen
void jsonHandler::saveToJson(QVector<adresses*> dataBaseVector)
{
    //Lager array json objekt
    QJsonArray jsonArray;
    //Går gjennom objekter i databasevektor og lagrer i jsonarray
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

//Tar mot string av filnavn og går gjennom json objekter, returnerer vektor med objektene
QVector<adresses*> jsonHandler::loadFromJson(QString filePath)
{
    //Lager ny vektor
    QVector<adresses*> arrayFromJson;

    //Lager fil objekt
    QFile file(filePath);

    //Hvis filen finnes
    if (file.exists()) {
        //Åpner filen med write only og lagrer objekter i array
        if (file.open(QIODevice::ReadWrite)) {
            QByteArray jsonData = file.readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
            QJsonArray jsonArray = jsonDoc.array();

            //Går gjennom alle objekter i array og legger til i vektor som nye objekter
            for(int i{0}; i < jsonArray.size(); i++)
            {
                adresses *tempContact = new adresses(
                            jsonArray.at(i)["name"].toString(),
                            jsonArray.at(i)["address"].toString(),
                            jsonArray.at(i)["postal"].toString(),
                            jsonArray.at(i)["email"].toString(),
                            jsonArray.at(i)["number"].toString());

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

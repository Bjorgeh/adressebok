#include "jsonhandler.h"

jsonHandler::jsonHandler()
{
    //skal sjekke om jsonfil finnes, hvis ikke lages den. og signal sendes.
    emit fileCreated("db.json");
}

void jsonHandler::saveToJson(QVector<adresses> dataBaseVector)
{
    //skal ta info fra vektor og skriver det inn i jsonfilen
    emit savedToFile("testname");
}

void jsonHandler::deleteFromJsonFile(int vectorPos)
{
    //skal slette objekt fra jsonfil ved hjelp av elements posisjon i vektor
    emit deletedFromFile("testname");
}

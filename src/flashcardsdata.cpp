#include "flashcardsdata.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QException>

QList<FlashcardSet> FlashCardsData::flashcards = QList<FlashcardSet>();
QString FlashCardsData::setsFilePath = "C:\\Users\\artyo\\Documents\\src\\C++\\Flashcards\\sets\\sets.json";

/*

        {
            "Name": "test set 1",
            "Terms": [
                {
                    "Key": "hallo",
                    "Value": "hello"
                }
                {
                    "Key": "Hund",
                    "Value": "dog"
                }
            ]
        },
        {
            "Name": "test set 2",
            "Terms": [
                {
                    "Key": "hallo",
                    "Value": "hello"
                }
            ]
        },
        {
            "Name": "test set 3",
            "Terms": [
                {
                    "Key": "hallo",
                    "Value": "hello"
                }
            ]
        }
        */

bool FlashCardsData::LoadSets(QString sLoadFilePath){
    setsFilePath = sLoadFilePath;
    QFile loadFile(sLoadFilePath);
    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug("Failed to open file\n");
        return false;
    }
    QByteArray bytes = loadFile.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &error);
    QJsonObject json = doc.object();

    auto setsArray = json["Sets"].toArray();
    for (auto set : setsArray) {
        qDebug() << "Adding flashcard";
        flashcards.push_back(FlashcardSet(set.toObject()));
    }
    loadFile.close();
    return true;
}
/*
 *
            {
            "Key": "hallo",
            "Value": "hello"
}
*/

bool FlashCardsData::SaveSets(QString sSaveFilePath) {
    QFile loadFile(sSaveFilePath);
    if (!loadFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Unable to open file for writing " << loadFile.errorString() << "\n";
        return false;
    }
    QJsonObject json;
    QJsonArray setsArray;
    for (auto set : flashcards) {
        QJsonObject setObject;
        set.generateJson(setObject);
        //qDebug() << setObject["Terms"].toArray()[0].toObject()["Key"].toString();
        setsArray.append(setObject);
    }
    json["Sets"] = setsArray;
    loadFile.write(QJsonDocument(json).toJson());
    loadFile.close();
    return true;
}

void FlashCardsData::setFlashcards(const QList<FlashcardSet> &newFlashcards)
{
    flashcards = newFlashcards;
}

QList<FlashcardSet> &FlashCardsData::getFlashcards()
{
    return flashcards;
}

FlashcardSet &FlashCardsData::getFlashcardSet(const QString &setName)
{
    for (int i = 0; i < flashcards.size(); i++) {
        if (flashcards[i].getName() == setName) {
            return flashcards[i];
        }
    }
    throw QUnhandledException();
}

bool FlashCardsData::flashcardSetExists(const QString &setName)
{
    for (int i = 0; i < flashcards.size(); i++) {
        if (flashcards[i].getName() == setName) {
            return true;
        }
    }
    return false;
}


void FlashCardsData::addFlashcardSet(const FlashcardSet set)
{
    flashcards.append(set);
}

void FlashCardsData::DeleteFlashcardSet(FlashcardSet set)
{
    DeleteFlashcardSet(set.getName());
}

void FlashCardsData::DeleteFlashcardSet(const QString &setName)
{
    for (int i = 0; i < flashcards.size(); i++) {
        if (flashcards[i].getName() == setName) {
            flashcards.removeAt(i);
            break;
        }
    }
}

void FlashCardsData::updateFlashcardSetTerm(const QString &setName, const QString &oldTerm, const QString &newTerm)
{
    for (int i = 0; i < flashcards.size(); i++) {
        if (flashcards[i].getName() == setName) {
            flashcards[i].updateKey(oldTerm, newTerm);
            break;
        }
    }
}

void FlashCardsData::updateFlashcardSetValue(const QString &setName, const QString &term, const QString &newValue)
{
    for (int i = 0; i < flashcards.size(); i++) {
        if (flashcards[i].getName() == setName) {
            flashcards[i].updateVal(term, newValue);
            break;
        }
    }
}

FlashCardsData::~FlashCardsData()
{
    SaveSets(setsFilePath);
}

FlashcardSet FlashCardsData::parseInputSet(QString& userInput, const QString& delim, const QString& setName, bool definitionFirst) {

    FlashcardSet tempSet;
    QTextStream textStream(&userInput);
    QString line;
    while (textStream.readLineInto(&line, 200)) {
        try {
            QList<QString> parts = line.split(delim, Qt::SkipEmptyParts);
            QString key, value;
            if (parts.size() != 2){ return {}; }
            if (definitionFirst){
                key = parts[1];
                value = parts[0];
            } else{
                key = parts[0];
                value = parts[1];
            }
            qDebug() << key.simplified() << value.simplified();
            tempSet[key.simplified()] = value.simplified();

        }  catch (QException& e) {
            return {};
        }
    }
    tempSet.setName(setName);
    return tempSet;
}

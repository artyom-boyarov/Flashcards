#ifndef FLASHCARDSDATA_H
#define FLASHCARDSDATA_H

#include <QString>
#include <QList>
#include "flashcardset.h"

class FlashCardsData
{
public:
    static bool LoadSets(QString setPath);
    static bool SaveSets(QString setPath);


    static void setFlashcards(const QList<FlashcardSet> &newFlashcards);
    static QList<FlashcardSet> &getFlashcards();
    static FlashcardSet& getFlashcardSet(const QString& setName);
    static bool flashcardSetExists(const QString& setName);

    static void addFlashcardSet(const FlashcardSet set);
    static void DeleteFlashcardSet(FlashcardSet set);
    static void DeleteFlashcardSet(const QString& setName);

    static void updateFlashcardSetTerm(const QString& setName, const QString& oldTerm, const QString& newTerm);
    static void updateFlashcardSetValue(const QString& setName, const QString& term, const QString& newValue);

    static FlashcardSet parseInputSet(QString& userInput, const QString& delim, const QString& setName, bool definitionFirst);
    ~FlashCardsData();

private:

    static QList<FlashcardSet> flashcards;
    static QString setsFilePath;

};

#endif // FLASHCARDSDATA_H

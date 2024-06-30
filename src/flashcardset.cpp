#include "flashcardset.h"

FlashcardSet::FlashcardSet()
{

}

FlashcardSet::FlashcardSet(QString name, QMap<QString, QString> terms) : name(name),
    terms(terms)
{

}

FlashcardSet::FlashcardSet(QJsonObject json)  {
    name = json["Name"].toString().simplified();
    for (auto jsonTerms : json["Terms"].toArray()) {
        QJsonObject c_obj = jsonTerms.toObject();
        terms[c_obj["Key"].toString()] = c_obj["Value"].toString().simplified();
    }
}


QString FlashcardSet::getName() const {
    return name;
}

void FlashcardSet::setName(QString newName) {
    name = newName;
}

QJsonObject FlashcardSet::generateJson(QJsonObject& json) {
    json["Name"] = this->name;
    QJsonArray termsJson;
    QMapIterator<QString, QString> termsIterator(terms);
    while (termsIterator.hasNext()) {
        termsIterator.next();
        qDebug() << "Key" << termsIterator.key() <<  "Value: " << termsIterator.value() << "\n";
        QJsonObject termJsonObject;
        termJsonObject.insert("Key", termsIterator.key());
        termJsonObject.insert("Value", termsIterator.value());
        termsJson.append(termJsonObject);
    }
    json["Terms"] = termsJson;
    return json;
}

const QMap<QString, QString> &FlashcardSet::getTerms() const
{
    return terms;
}

void FlashcardSet::setTerms(const QMap<QString, QString> &newTerms)
{
    terms = newTerms;
}

QString &FlashcardSet::operator[](const QString &key)
{
    return terms[key];
}

void FlashcardSet::updateKey(const QString &oldKey, const QString &newKey)
{
    QString defn = terms[oldKey];
    terms.remove(oldKey);
    terms.insert(newKey, defn);
}

void FlashcardSet::updateVal(const QString &key, const QString &newVal)
{
    qDebug() << "Changing " << key << " to " << newVal;
    terms[key] = newVal;
    qDebug() << "Now " << terms[key];
}

FlashcardSet::operator bool() const
{
    return terms.size() > 0; // If size > 0, then the set is initialized.
}

QMapIterator<QString, QString> FlashcardSet::getTermIterator()
{
    return QMapIterator<QString, QString>(terms);
}


bool operator==(FlashcardSet& s1, FlashcardSet& s2) {
    if (s1.getName() != s2.getName()) return false;
    if (s1.getTerms().size() != s1.getTerms().size()) return false;
    if (s1.getTerms() != s2.getTerms()) return false;
    return true;
}

#ifndef SETVIEW_H
#define SETVIEW_H

#include <memory>

#include <QWidget>

#include "flashcardset.h"
#include "flashcardsdata.h"

namespace Ui {
class SetView;
}

class SetView : public QWidget
{
    Q_OBJECT

public:
    explicit SetView(QWidget *parent = nullptr);
    ~SetView();

    const QString setName() const;
    void setSet(const QString& newSetName);

signals:
    void RequestGoBack();
    void ReviseSet(const QString& setName);
    //void LearnSet(FlashcardSet& set);

public slots:
    void on_homeButton_clicked();

    void on_editButton_clicked();

    void on_reviseButton_clicked();

    void on_learnButton_clicked();

private slots:
    void on_deleteButton_clicked();

    void on_termsTable_cellChanged(int row, int column);

    void on_termsTable_cellActivated(int row, int column);

    void on_termsTable_cellDoubleClicked(int row, int column);

private:
    Ui::SetView *ui;
    QString mSetName; // Name of the set to show.

    QList<QWidget*> setLabels;
    QString editedTerm = "", editedDefn = "";
};

#endif // SETVIEW_H

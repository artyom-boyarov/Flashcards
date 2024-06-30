#ifndef IMPORTSETDIALOG_H
#define IMPORTSETDIALOG_H

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <QMap>
#include "flashcardset.h"
#include "flashcardsdata.h"

namespace Ui {
class ImportSetDialog;
}

class ImportSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportSetDialog(QWidget *parent = nullptr, bool importFromFile = true);
    ~ImportSetDialog();

private slots:
    void on_chooseFileButton_clicked();

    void on_previewButton_clicked();

    void on_importButton_clicked();


private:
    Ui::ImportSetDialog *ui;
    QString mFileName;
    QMap<QString, QString> mTerms;
    FlashcardSet mTempSet;

    FlashcardSet LoadSet();

    void LoadSetError();
};

#endif // IMPORTSETDIALOG_H

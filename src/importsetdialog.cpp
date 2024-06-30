#include "importsetdialog.h"
#include "ui_importsetdialog.h"
#include <stdexcept>
#include <QException>
#include <QtAlgorithms>
#include "welcomeview.h"
#include "previewdialog.h"
#include <QMessageBox>

ImportSetDialog::ImportSetDialog(QWidget *parent, bool importFromFile) :
    QDialog(parent),
    ui(new Ui::ImportSetDialog)
{
    ui->setupUi(this);
    if (!importFromFile) {
        ui->chooseFileButton->hide();
        ui->dialogLabel->setText("Create set");
        ui->setInput->setPlaceholderText("Start writing your term/definition pairs separated by the delimeter, with each pair on its own line");
        setWindowTitle("Create set");
    }
}

ImportSetDialog::~ImportSetDialog()
{
    delete ui;
}

void ImportSetDialog::on_chooseFileButton_clicked()
{
    mFileName = QFileDialog::getOpenFileName(this, "Choose file with set");
    QFile loadFile(mFileName);
    qDebug() << mFileName;
    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
    }
    else ui->setInput->setText(loadFile.readAll());
}

FlashcardSet ImportSetDialog::LoadSet()
{
    QString name = ui->nameEdit->text();
    if (name == "") {
        QMessageBox::warning(this, "Name is empty", "Please enter a name for your set");
        return {};
    }

    if (FlashCardsData::flashcardSetExists(name)) {
        QMessageBox::warning(this, "Set with given name already exists", tr("Name \"%1\" is unavailable. Please choose another name").arg(name));
        return {};
    }

    QString delim = ui->delimEdit->text();
    QString setData = ui->setInput->toPlainText();
    if (setData == "") {
        QMessageBox::warning(this, "Set data is empty", "Please enter your set data");
        return {};
    }
    bool definitionFirst = ui->defFirstButton->isChecked();
    auto set = FlashCardsData::parseInputSet(setData, delim, name, definitionFirst);
    if (!set) {
        QMessageBox::warning(this, "Unable to parse input", "Please enter your set data correctly. Each key/value pair is on its own line, separated by your defined delimeter");
        return {};
    }
    return set;
}

void ImportSetDialog::LoadSetError()
{
    QMessageBox::critical(this, "Error loading set", "Error when loading set. Check you have entered the set correctly");
}


void ImportSetDialog::on_previewButton_clicked()
{
    auto set = LoadSet();
    if (!set){ return; }
    PreviewDialog* dialog = new PreviewDialog(set);
    dialog->show();
}


void ImportSetDialog::on_importButton_clicked()
{
    auto set = LoadSet();
    if (!set) { return; }
    FlashCardsData::addFlashcardSet(set);
    close();
}


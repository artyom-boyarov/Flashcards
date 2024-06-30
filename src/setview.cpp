#include "setview.h"
#include "ui_setview.h"
#include <QMessageBox>
// TODO: edit set
SetView::SetView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetView)
{
    ui->setupUi(this);
    ui->termsTable->setHorizontalHeaderLabels({"Term", "Definition"});
    ui->termsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

SetView::~SetView()
{
    delete ui;
}

void SetView::on_homeButton_clicked()
{
    editedDefn = "";
    editedTerm  = "";
    emit RequestGoBack();
}

const QString SetView::setName() const
{
    return mSetName;
}

void SetView::setSet(const QString& newSetName)
{
    mSetName = newSetName;
    ui->setName->setText(mSetName);

    auto set = FlashCardsData::getFlashcardSet(mSetName);
    auto terms = set.getTerms();
    ui->termsTable->setHorizontalHeaderLabels({"Term", "Definition"});
    ui->termsTable->setRowCount(terms.size());
    ui->termsTable->setColumnCount(2);
    QMapIterator<QString, QString> setIterator(terms);

    size_t idx = 0;
    while (setIterator.hasNext()) {
        setIterator.next();
        QTableWidgetItem *keyItem = new QTableWidgetItem(setIterator.key());
        QTableWidgetItem *valItem = new QTableWidgetItem(setIterator.value());
        ui->termsTable->setItem(idx, 0, keyItem);
        ui->termsTable->setItem(idx, 1, valItem);
        idx++;
    }
}


void SetView::on_editButton_clicked()
{

}


void SetView::on_reviseButton_clicked()
{
    qDebug() << "Revising set " << mSetName;
    emit ReviseSet(mSetName);
}


void SetView::on_learnButton_clicked()
{

}


void SetView::on_deleteButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Delete set?");
    msgBox.setInformativeText("Confirm");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Cancel)  {
        return;
    }
    FlashCardsData::DeleteFlashcardSet(mSetName);
    mSetName = "";
}


void SetView::on_termsTable_cellChanged(int row, int column)
{
    qDebug() << "Cell " << row << ", " << column << " edited";
    if (column  == 0) {
        if (editedDefn != "" && editedTerm != "") {
            // Key changed
            auto newKey = ui->termsTable->item(row, 0)->text();
            FlashCardsData::updateFlashcardSetTerm(mSetName, editedTerm, newKey);
        }
    }
    else {
        if (editedDefn != "" && editedTerm != "") {
            // Value changed
            qDebug() << "Changing to " << ui->termsTable->item(row, 1)->text();
            FlashCardsData::updateFlashcardSetValue(mSetName, editedTerm, ui->termsTable->item(row, 1)->text());
        }
    }
}


void SetView::on_termsTable_cellActivated(int row, int column)
{
}


void SetView::on_termsTable_cellDoubleClicked(int row, int column)
{
    qDebug() << "Cell " << row << ", " << column << " double clicked";
    editedTerm = ui->termsTable->item(row, 0)->text();
    editedDefn = ui->termsTable->item(row, 1)->text();
}


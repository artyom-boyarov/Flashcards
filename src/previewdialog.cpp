#include "previewdialog.h"
#include "ui_previewdialog.h"
#include <QLabel>
#include <QTableWidget>

PreviewDialog::PreviewDialog(const FlashcardSet& setToPreview, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviewDialog)
{
    ui->setupUi(this);
    auto setToPreviewTerms = setToPreview.getTerms();
    QMapIterator<QString, QString> it(setToPreviewTerms);
    ui->previewTable->setRowCount(setToPreviewTerms.size());
    ui->previewTable->setColumnCount(2);
    size_t idx = 0;
    while (it.hasNext()) {
        it.next();
        QTableWidgetItem *keyItem = new QTableWidgetItem(it.key());
        QTableWidgetItem *valItem = new QTableWidgetItem(it.value());
        ui->previewTable->setItem(idx, 0, keyItem);
        ui->previewTable->setItem(idx, 1, valItem);
        idx++;
    }

    ui->previewTable->setHorizontalHeaderLabels({"Term", "Definition"});
    ui->previewTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

PreviewDialog::~PreviewDialog()
{
    delete ui;
}

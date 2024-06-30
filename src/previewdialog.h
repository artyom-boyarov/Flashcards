#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>
#include <QMap>
#include <QString>
#include "flashcardset.h"

namespace Ui {
class PreviewDialog;
}

class PreviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewDialog(const FlashcardSet& setToPreview, QWidget *parent = nullptr);
    ~PreviewDialog();

private:
    Ui::PreviewDialog *ui;
};

#endif // PREVIEWDIALOG_H

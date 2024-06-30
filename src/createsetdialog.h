#ifndef CREATESETDIALOG_H
#define CREATESETDIALOG_H

#include <QDialog>

namespace Ui {
class CreateSetDialog;
}

class CreateSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateSetDialog(QWidget *parent = nullptr);
    ~CreateSetDialog();

private:
    Ui::CreateSetDialog *ui;
};

#endif // CREATESETDIALOG_H

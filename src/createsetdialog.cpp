#include "createsetdialog.h"
#include "ui_createsetdialog.h"

CreateSetDialog::CreateSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateSetDialog)
{
    ui->setupUi(this);
}

CreateSetDialog::~CreateSetDialog()
{
    delete ui;
}

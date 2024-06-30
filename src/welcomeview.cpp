
#include "welcomeview.h"
#include "ui_welcomeview.h"
#include "flashcardsdata.h"
#include "importsetdialog.h"
#include "createsetdialog.h"
#include <QGroupBox>
#include <QLabel>
#include <QSizePolicy>

WelcomeView::WelcomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeView)
{
    ui->setupUi(this);
    scrollLayout = new QVBoxLayout;
    mainBox = new QGroupBox;
    mainBox->setLayout(scrollLayout);
    ui->setView->setWidget(mainBox);

    Refresh();
}

WelcomeView::~WelcomeView()
{
    delete ui;
}

void WelcomeView::Refresh()
{
    for (auto button: setButtons) {
        scrollLayout->removeWidget(button);
        delete button;
    }
    setButtons.clear();
    setupLayout();

}

void WelcomeView::on_importCreateDialog_close()
{
    qDebug() << "Closed";
    Refresh();
}

void WelcomeView::setupLayout()
{
    if (FlashCardsData::getFlashcards().size() == 0) {
        QLabel* noSetsLabel = new QLabel("<i>No sets</i>");
        noSetsLabel->setAlignment(Qt::AlignHCenter);
        scrollLayout->addWidget(noSetsLabel);
    }

    for (const auto& set : FlashCardsData::getFlashcards()) {
        QPushButton* setButton = new QPushButton(set.getName());

        auto buttonFont = setButton->font();
        buttonFont.setPointSize(12);
        setButton->setFont(buttonFont);

        QObject::connect(setButton, &QPushButton::clicked, this, [=]() {
            emit GotoSet(set.getName());
        });

        setButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        scrollLayout->addWidget(setButton);
        setButtons.append(setButton);
    }
}


void WelcomeView::on_createSetButton_clicked()
{
    ImportSetDialog* createSetDialog = new ImportSetDialog(nullptr, false);
    createSetDialog->show();
    QObject::connect(createSetDialog, &CreateSetDialog::finished, this, &WelcomeView::on_importCreateDialog_close);
}


void WelcomeView::on_importSetButton_clicked()
{
    ImportSetDialog* importDialog = new ImportSetDialog(this);
    importDialog->show();
    QObject::connect(importDialog, &ImportSetDialog::finished, this, &WelcomeView::on_importCreateDialog_close);
}


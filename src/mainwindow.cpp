#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include "flashcardsdata.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (!FlashCardsData::LoadSets(setPath)) {
        qDebug() << "Failed to load sets";
    }

    welcomeView = new WelcomeView;
    setView = new SetView;
    reviseView = new ReviseView;


    QObject::connect(welcomeView, &WelcomeView::GotoSet, this, &MainWindow::OnSetButtonClicked);
    QObject::connect(setView, &SetView::RequestGoBack, this, &MainWindow::OnGoBackRequest);
    QObject::connect(setView, &SetView::ReviseSet, this , &MainWindow::OnReviseSet);
    QObject::connect(reviseView, &ReviseView::ReturnToSet, this, &MainWindow::OnGoBackToSet);
    QObject::connect(this, &MainWindow::GotoWidget, ui->mainStack, &QStackedWidget::setCurrentWidget);

    ui->mainStack->addWidget(welcomeView);
    ui->mainStack->addWidget(setView);
    ui->mainStack->addWidget(reviseView);
    ui->mainStack->setCurrentWidget(welcomeView);
}

MainWindow::~MainWindow()
{
    qDebug() << "Saving sets";
    FlashCardsData::SaveSets(setPath);
    delete ui;
}

void MainWindow::OnSetButtonClicked(const QString& setName)
{
    qDebug() << "Selected " << setName;

    setView->setSet(setName);
    emit GotoWidget(setView);
}

void MainWindow::OnGoBackRequest()
{
    emit GotoWidget(welcomeView);
}

void MainWindow::OnReviseSet(const QString& setName)
{
    qDebug() << "Revising " << setName;
    reviseView->setSet(setName);
    emit GotoWidget(reviseView);

}

void MainWindow::OnGoBackToSet()
{
    emit GotoWidget(setView);
}


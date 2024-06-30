#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QMap>
#include "flashcardset.h"
#include <QVBoxLayout>
#include "setview.h"
#include <QStackedLayout>
#include <QStackedWidget>
#include <QGroupBox>
#include "welcomeview.h"
#include "reviseview.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void OnSetButtonClicked(const QString& setName);
    void OnGoBackRequest();
    void OnReviseSet(const QString& setName);
    void OnGoBackToSet();

signals:
    void GotoWidget(QWidget*);

private:

    QList<FlashcardSet> sets;

    QString setPath = "C:\\Users\\artyo\\Documents\\src\\C++\\Flashcards\\sets\\sets.json";
    WelcomeView* welcomeView;
    SetView* setView;
    ReviseView* reviseView;


    QStackedLayout* mainStack;
    QVBoxLayout* mainLayout;
    QGroupBox* mainBox;

    Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H

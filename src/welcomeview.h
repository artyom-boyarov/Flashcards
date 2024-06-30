#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>
#include <QList>
#include <QPushButton>
#include "flashcardset.h"
#include <QVBoxLayout>
#include <QGroupBox>

namespace Ui {
class WelcomeView;
}

class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeView(QWidget *parent = nullptr);
    ~WelcomeView();
    void Refresh();

signals:
    // Causes the view to switch to show the selected set
    void GotoSet(const QString& setName);
private slots:
    void on_importCreateDialog_close();

    void on_createSetButton_clicked();

    void on_importSetButton_clicked();

private:
    Ui::WelcomeView *ui;

    void     setupLayout();
    QList<QPushButton*> setButtons{};

    QVBoxLayout* scrollLayout;
    QGroupBox* mainBox;
};

#endif // WELCOMEVIEW_H

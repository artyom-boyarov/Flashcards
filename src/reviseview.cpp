#include "reviseview.h"
#include "ui_reviseview.h"
#include <QMessageBox>

ReviseView::ReviseView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReviseView),
    mSetName{}
{
    ui->setupUi(this);
}

ReviseView::~ReviseView()
{
    delete ui;
}

const QString& ReviseView::setName() const
{
    return mSetName;
}

void ReviseView::setSet(const QString& newSetName)
{
    mSetName = newSetName;
    auto set = FlashCardsData::getFlashcardSet(mSetName);
    QMapIterator<QString, QString> termsIterator = set.getTermIterator();
    mTermsQueue.clear();
    while (termsIterator.hasNext()) {
        termsIterator.next();
        mTermsQueue.append( qMakePair(termsIterator.key(), termsIterator.value()));
    }
    Begin();
}

void ReviseView::Begin()
{
    state = State::CHECK;
    terms_done = 0;
    ui->progressBar->setRange(0, mTermsQueue.size());
    ui->textInput->setPlaceholderText("");
    ui->progressBar->setValue(0);
    if (mTermsQueue.size() == 0) {
        qErrnoWarning("No terms in set");
        emit ReturnToSet();
    }
    mCurrentTerm = mTermsQueue.dequeue();
    ui->keyLabel->setText(mCurrentTerm.first);
}

void ReviseView::StartLearning(FlashcardSet &set)
{
    qDebug() << "Learning " << set.getName();
}

void ReviseView::on_homeButton_clicked()
{
    emit ReturnToSet();
}


void ReviseView::on_checkButton_clicked()
{

    QString key = mCurrentTerm.first;
    QString value = mCurrentTerm.second;

    QString input = ui->textInput->text();

    if (state == State::CHECK) {
        if (input != value) {
            // Wrong - go to check
            state = State::RETYPE;
            ui->statusLabel->setText( "Incorrect - please retype!");

            ui->textInput->clear();
            ui->textInput->setPlaceholderText(value);
            mTermsQueue.enqueue(mCurrentTerm);

        } else {
            terms_done++;
            SetNextTerm();
        }

    } else {
        if (input != value) {
            // Wrong
            ui->statusLabel->setText("Incorrect - please type in the correct word!");
        } else {
            SetNextTerm();
        }
    }
}

void ReviseView::SetNextTerm()
{
    state = State::CHECK;
    ui->statusLabel->setText("Correct!");
    if (mTermsQueue.size() > 0)
    {
        mCurrentTerm = mTermsQueue.dequeue();
        ui->progressBar->setValue(terms_done);
        ui->textInput->clear();
        ui->textInput->setPlaceholderText("");
        ui->keyLabel->setText(mCurrentTerm.first);
    } else {
        QMessageBox::information(this, "Finished revising", tr("You've completed revising set %1! Well done!").arg(mSetName));
        emit ReturnToSet();
    }

}


void ReviseView::on_textInput_returnPressed()
{
    on_checkButton_clicked();
}


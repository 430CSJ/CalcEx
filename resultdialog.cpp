#include "resultdialog.h"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(ExData *exD, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    exData = exD;
    ui->setupUi(this);
    int y = 0;
    QWidget *scrollArea = ui->scrollAreaWidgetContents;
    int buyNum, sellNum;
    for (int i = 0; i < 3; ++i)
    {
        if (!exData->isExSelected[i])
            continue;
        QString title;
        QLabel *titleLabel;
        QPalette pe;
        switch (i) {
        case 0:
            title = "翻打";
            titleLabel = new QLabel(title, scrollArea);
            titleLabel->setGeometry(0, y, 600, 40);
            titleLabel->show();
            y += 40;
            for (int j= 0; j < 3; ++j)
            {
                for (int k = 0; k < 51; ++k)
                {
                    if (k == exData->exDelLine[i])
                        continue;
                    qlonglong input = exData->ex1Input[j][k], answer = exData->ex1Data[j][k];
                    QLabel *numL = new QLabel(QString::number(k + 1), scrollArea), *inL = new QLabel(QString::number(input), scrollArea), *ansL = new QLabel(QString::number(answer), scrollArea);
                    numL->setGeometry(0, y, 100, 30);
                    numL->show();
                    if (input == answer)
                        pe.setColor(QPalette::WindowText, Qt::green);
                    else
                        pe.setColor(QPalette::WindowText, Qt::red);
                    inL->setGeometry(100, y, 250, 30);
                    inL->setPalette(pe);
                    inL->show();
                    ansL->setGeometry(350, y, 250, 30);
                    ansL->setPalette(pe);
                    ansL->show();
                    y += 30;
                }
                y += 30;
            }
            y += 30;
            break;
        case 1:
            title = "平打";
            titleLabel = new QLabel(title, scrollArea);
            titleLabel->setGeometry(0, y, 600, 40);
            titleLabel->show();
            y += 40;
            for (int j= 0; j < 3; ++j)
            {
                for (int k = 0; k < 51; ++k)
                {
                    if (k == exData->exDelLine[i])
                        continue;
                    qlonglong input = exData->ex2Input[j][k], answer = exData->ex2Data[j][k];
                    QLabel *numL = new QLabel(QString::number(k + 1), scrollArea), *inL = new QLabel(QString::number(input), scrollArea), *ansL = new QLabel(QString::number(answer), scrollArea);
                    numL->setGeometry(0, y, 100, 30);
                    numL->show();
                    if (input == answer)
                        pe.setColor(QPalette::WindowText, Qt::green);
                    else
                        pe.setColor(QPalette::WindowText, Qt::red);
                    inL->setGeometry(100, y, 250, 30);
                    inL->setPalette(pe);
                    inL->show();
                    ansL->setGeometry(350, y, 250, 30);
                    ansL->setPalette(pe);
                    ansL->show();
                    y += 30;
                }
                y += 30;
            }
            y += 30;
            break;
        case 2:
            title = "外汇折算";
            titleLabel = new QLabel(title, scrollArea);
            titleLabel->setGeometry(0, y, 600, 40);
            titleLabel->show();
            y += 40;
            buyNum = exData->ex3BuyInput.size();
            for (int k = 0; k < buyNum; ++k)
            {
                QString inS = exData->ex3BuyInput.at(k);
                QString ansS = exData->ex3BuyAnswer.at(k);
                QLabel *numL = new QLabel(QString::number(k + 1), scrollArea), *inL = new QLabel(inS, scrollArea), *ansL = new QLabel(ansS, scrollArea);
                numL->setGeometry(0, y, 100, 30);
                numL->show();
                if (QString::compare(inS, ansS) == 0)
                    pe.setColor(QPalette::WindowText, Qt::green);
                else
                    pe.setColor(QPalette::WindowText, Qt::red);
                inL->setGeometry(100, y, 250, 30);
                inL->setPalette(pe);
                inL->show();
                ansL->setGeometry(350, y, 250, 30);
                ansL->setPalette(pe);
                ansL->show();
                y += 30;
            }
            y += 30;
            sellNum = exData->ex3SellInput.size();
            for (int k = 0; k < buyNum; ++k)
            {
                QString inS = exData->ex3SellInput.at(k);
                QString ansS = exData->ex3SellAnswer.at(k);
                QLabel *numL = new QLabel(QString::number(k + 1), scrollArea), *inL = new QLabel(inS, scrollArea), *ansL = new QLabel(ansS, scrollArea);
                numL->setGeometry(0, y, 100, 30);
                numL->show();
                if (QString::compare(inS, ansS) == 0)
                    pe.setColor(QPalette::WindowText, Qt::green);
                else
                    pe.setColor(QPalette::WindowText, Qt::red);
                inL->setGeometry(100, y, 250, 30);
                inL->setPalette(pe);
                inL->show();
                ansL->setGeometry(350, y, 250, 30);
                ansL->setPalette(pe);
                ansL->show();
                y += 30;
            }
            y += 60;
            break;
        default:
            break;
        }
    }
    scrollArea->setMinimumSize(0, y);
}

ResultDialog::~ResultDialog()
{
    delete ui;
}

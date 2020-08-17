#include "ex3dialog.h"
#include "ui_ex3dialog.h"

Ex3Dialog::Ex3Dialog(ExData *exD, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ex3Dialog)
{
    exData = exD;
    ui->setupUi(this);
    unsigned time_left = exD->timeLeft, minute = (time_left % 3600) / 60, second = time_left % 60;
    QString timestr = QString::number(time_left / 3600).append(':'), winTitle = "外汇折算";
    if (minute < 10)
        timestr.append('0');
    timestr.append(QString::number(minute)).append(':');
    if (second < 10)
        timestr.append('0');
    timestr.append(QString::number(second));
    setWindowTitle(winTitle.append("    考试时间倒计时：").append(timestr));
    if (exData->timeLeft == 0)
    {
        QMessageBox::question(this, "提示", tr("时间到。"), QMessageBox::Yes, QMessageBox::Yes);
        accept();
    }
    QWidget *rightArea = ui->scrollAreaWidgetContents_2, *leftArea = ui->scrollAreaWidgetContents;
    QLabel *rightTitle = new QLabel("汇率表", rightArea);
    rightTitle->setGeometry(0, 0, 100, 50);
    rightTitle->show();
    QLabel *codeH = new QLabel("代号", rightArea),
            *kindH = new QLabel("币种", rightArea),
            *kindSH = new QLabel("币种缩写", rightArea),
            *buy0H = new QLabel("购汇买入", rightArea),
            *buy1H = new QLabel("现钞买入", rightArea),
            *sellH = new QLabel("卖出价", rightArea);
    codeH->setGeometry(0, 50, 40, 40);
    codeH->show();
    kindH->setGeometry(40, 50, 80, 40);
    kindH->show();
    kindSH->setGeometry(120, 50, 80, 40);
    kindSH->show();
    buy0H->setGeometry(200, 50, 104, 40);
    buy0H->show();
    buy1H->setGeometry(304, 50, 104, 40);
    buy1H->show();
    sellH->setGeometry(408, 50, 104, 40);
    sellH->show();
    int y = 50 + 40;
    QList<QList<QByteArray>> *ertp = &exData->ert;
    for (int i = 0; i < ertp->size(); ++i)
    {
        QLabel *labels[6];
        for (int j = 0; j < 6; ++j)
            labels[j] = new QLabel(QTextCodec::codecForName("UTF-8")->toUnicode(ertp->at(i).at(j)), rightArea);
        labels[0]->setGeometry(0, y, 40, 40);
        labels[1]->setGeometry(40, y, 100, 40);
        labels[2]->setGeometry(140, y, 60, 40);
        labels[3]->setGeometry(200, y, 104, 40);
        labels[4]->setGeometry(304, y, 104, 40);
        labels[5]->setGeometry(408, y, 104, 40);
        for (int j = 0; j < 6; ++j)
            labels[j]->show();
        y += 40;
    }
    rightArea->setMinimumSize(0, y);
    QLabel *leftTitle0 = new QLabel("一、将外汇按汇买价折算成人民币。", leftArea);
    leftTitle0->setGeometry(0, 0, 500, 50);
    leftTitle0->show();
    QList<double> buycnts = exData->buyCnts;
    y = 50;
    for (int i = 0; i < buycnts.size(); ++i)
    {
        QLabel *label = new QLabel(QTextCodec::codecForName("UTF-8")->toUnicode(exData->codeNames.value(exData->buyCodes.at(i), "")).append(' ').append(QString::number(buycnts.at(i), 'f', 2)).append(" = RMB"), leftArea), *labelN = new QLabel(QString::number(i + 1), leftArea);
        labelN->setGeometry(0, y, 50, 40);
        labelN->show();
        label->setGeometry(50, y, 250, 40);
        label->show();
        buyLineEdits.push_back(new Ex3BuyLineEdit(leftArea));
        buyLineEdits.back()->i = i;
        buyLineEdits.back()->exData = exD;
        buyLineEdits.back()->setGeometry(300, y, 160, 40);
        buyLineEdits.back()->show();
        connect(buyLineEdits.back(), SIGNAL(calcB(int)), this, SLOT(nextB(int)));
        y += 40;
    }
    QLabel *leftTitle1 = new QLabel("二、将人民币按汇卖价折算成外币。", leftArea);
    leftTitle1->setGeometry(0, y, 500, 50);
    leftTitle1->show();
    QList<double> sellcnts = exData->sellCnts;
    y += 50;
    for (int i = 0; i < sellcnts.size(); ++i)
    {
        QString str = "RMB ";
        str.append(QString::number(sellcnts.at(i), 'f', 2).append(" = ").append(QTextCodec::codecForName("UTF-8")->toUnicode(exData->codeNames.value(exData->sellCodes.at(i), ""))));
        QLabel *label = new QLabel(str, leftArea), *labelN = new QLabel(QString::number(i + 1), leftArea);
        labelN->setGeometry(0, y, 50, 40);
        labelN->show();
        label->setGeometry(50, y, 250, 40);
        label->show();
        sellLineEdits.push_back(new Ex3SellLineEdit(leftArea));
        sellLineEdits.back()->i = i;
        sellLineEdits.back()->exData = exD;
        sellLineEdits.back()->setGeometry(300, y, 160, 40);
        sellLineEdits.back()->show();
        connect(sellLineEdits.back(), SIGNAL(calcS(int)), this, SLOT(nextS(int)));
        y += 40;
    }
    leftArea->setMinimumSize(0, y + 200);
    PrepareDialog *prepareDialog = new PrepareDialog("请做好准备。", this);
    prepareDialog->exec();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTimeLeft()));
    buyLineEdits.front()->setFocus();
    timer->start(1000);
}

Ex3Dialog::~Ex3Dialog()
{
    timer->stop();
    delete ui;
}

void Ex3Dialog::accept()
{
    timer->stop();
    QDialog::accept();
}

void Ex3Dialog::reject()
{
    if (QMessageBox::question(this, "提示", "结束练习？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
    {
        timer->stop();
        QDialog::reject();
    }
}

void Ex3Dialog::showTimeLeft()
{
    --exData->timeLeft;
    unsigned time_left = exData->timeLeft, minute = (time_left % 3600) / 60, second = time_left % 60;
    QString timestr = QString::number(time_left / 3600).append(':'), winTitle = "外汇折算";
    if (minute < 10)
        timestr.append('0');
    timestr.append(QString::number(minute)).append(':');
    if (second < 10)
        timestr.append('0');
    timestr.append(QString::number(second));
    setWindowTitle(winTitle.append("    考试时间倒计时：").append(timestr));
    if (time_left == 0)
    {
        timer->stop();
        QMessageBox::question(this, "提示", tr("时间到。"), QMessageBox::Yes, QMessageBox::Yes);
        accept();
    }
}

void Ex3Dialog::nextB(int i)
{
    QScrollBar *qsb = ui->scrollArea->verticalScrollBar();
    if (i == 19)
    {
        sellLineEdits.at(0)->setFocus();
        int sah = ui->scrollArea->height(), lee = sellLineEdits.at(0)->y() + sellLineEdits.at(0)->height();
        if (qsb != nullptr && qsb->value() + sah < lee)
            qsb->setValue(lee - sah);
    }
    else
    {
        buyLineEdits.at(i + 1)->setFocus();
        int sah = ui->scrollArea->height(), lee = buyLineEdits.at(i + 1)->y() + buyLineEdits.at(i + 1)->height();
        if (qsb != nullptr && qsb->value() + sah < lee)
            qsb->setValue(lee - sah);
    }
}

void Ex3Dialog::nextS(int i)
{
    if (i < 19)
    {
        sellLineEdits.at(i + 1)->setFocus();
        QScrollBar *qsb = ui->scrollArea->verticalScrollBar();
        int sah = ui->scrollArea->height(), lee = sellLineEdits.at(i + 1)->y() + sellLineEdits.at(i + 1)->height();
        if (qsb != nullptr && qsb->value() + sah < lee)
            qsb->setValue(lee - sah);
    }
}

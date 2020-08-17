#include "ex2dialog.h"
#include "ui_ex2dialog.h"

Ex2Dialog::Ex2Dialog(ExData *exD, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ex2Dialog)
{
    exData = exD;
    currentLine = 0;
    if (exData->exDelLine[1] == 0)
        currentLine = 1;
    ui->setupUi(this);
    labelC[0] = ui->label_c_1;
    labelC[1] = ui->label_c_2;
    labelC[2] = ui->label_c_3;
    labelL[0] = ui->label_l_1;
    labelL[1] = ui->label_l_2;
    labelL[2] = ui->label_l_3;
    labelT[0] = ui->label_t_1;
    labelT[1] = ui->label_t_2;
    labelT[2] = ui->label_t_3;
    unsigned time_left = exD->timeLeft, minute = (time_left % 3600) / 60, second = time_left % 60;
    QString timestr = QString::number(time_left / 3600).append(':');
    if (minute < 10)
        timestr.append('0');
    timestr.append(QString::number(minute)).append(':');
    if (second < 10)
        timestr.append('0');
    timestr.append(QString::number(second));
    ui->label_time_left->setText(timestr);
    ex2LineEdit[0] = ui->lineEdit_1;
    ex2LineEdit[1] = ui->lineEdit_2;
    ex2LineEdit[2] = ui->lineEdit_3;
    for (int i = 0; i < 3; ++i)
    {
        Ex2LineEdit *e2le = ex2LineEdit[i];
        e2le->colNum = i;
        QRegExp regx("[0-9]+$");
        QValidator *validator = new QRegExpValidator(regx, e2le);
        e2le->setValidator(validator);
        connect(e2le, SIGNAL(plus(int)), this, SLOT(plusCur(int)));
        connect(e2le, SIGNAL(minus(int)), this, SLOT(minusCur(int)));
        connect(e2le, SIGNAL(del(int)), this, SLOT(delLast(int)));
        connect(e2le, SIGNAL(next(int)), this, SLOT(nextCol(int)));
    }
    if (time_left == 0)
    {
        QMessageBox::question(this, "提示", tr("时间到。"), QMessageBox::Yes, QMessageBox::Yes);
        accept();
    }
    QString noticeStr = "去掉第 ";
    PrepareDialog *prepareDialog = new PrepareDialog(noticeStr.append(QString::number(exData->exDelLine[1] + 1)).append(" 行。"), this);
    prepareDialog->exec();
    ex2LineEdit[0]->setEnabled(true);
    ex2LineEdit[0]->setFocus();
    labelL[0]->setText(QString::number(currentLine));
    labelC[0]->setText(sumStr(sumCol(0)));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTimeLeft()));
    timer->start(1000);
}

Ex2Dialog::~Ex2Dialog()
{
    timer->stop();
    delete ui;
}

void Ex2Dialog::accept()
{
    timer->stop();
    QDialog::accept();
}

void Ex2Dialog::reject()
{
    if (QMessageBox::question(this, "提示", "结束练习？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
    {
        timer->stop();
        QDialog::reject();
    }
}

void Ex2Dialog::on_lineEdit_1_cursorPositionChanged(int arg1, int arg2)
{
    ex2LineEdit[0]->setCursorPosition(ex2LineEdit[0]->text().size());
}

void Ex2Dialog::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2)
{
    ex2LineEdit[1]->setCursorPosition(ex2LineEdit[1]->text().size());
}

void Ex2Dialog::on_lineEdit_3_cursorPositionChanged(int arg1, int arg2)
{
    ex2LineEdit[2]->setCursorPosition(ex2LineEdit[2]->text().size());
}

void Ex2Dialog::showTimeLeft()
{
    --exData->timeLeft;
    unsigned time_left = exData->timeLeft, minute = (time_left % 3600) / 60, second = time_left % 60;
    QString timestr = QString::number(time_left / 3600).append(':');
    if (minute < 10)
        timestr.append('0');
    timestr.append(QString::number(minute)).append(':');
    if (second < 10)
        timestr.append('0');
    timestr.append(QString::number(second));
    ui->label_time_left->setText(timestr);
    if (time_left == 0)
    {
        timer->stop();
        QMessageBox::question(this, "提示", tr("时间到。"), QMessageBox::Yes, QMessageBox::Yes);
        accept();
    }
}

void Ex2Dialog::plusCur(int curCol)
{
    Ex2LineEdit *e2le = ex2LineEdit[curCol];
    QString inputTxt = e2le->text();
    if (QString::compare(inputTxt, "") != 0)
    {
        if (currentLine < 51)
            exData->ex2Input[curCol][currentLine] = inputTxt.toLongLong();
        if (++currentLine == exData->exDelLine[1])
            ++currentLine;
        e2le->setText("");
        labelL[curCol]->setText(QString::number(currentLine + 1));
        labelC[curCol]->setText(sumStr(sumCol(curCol)));
    }
}

void Ex2Dialog::minusCur(int curCol)
{
    Ex2LineEdit *e2le = ex2LineEdit[curCol];
    QString inputTxt = e2le->text();
    if (QString::compare(inputTxt, "") != 0)
    {
        if (currentLine < 51)
            exData->ex2Input[curCol][currentLine] = 0 - inputTxt.toLongLong();
        if (++currentLine == exData->exDelLine[1])
            ++currentLine;
        e2le->setText("");
        labelL[curCol]->setText(QString::number(currentLine + 1));
        labelC[curCol]->setText(sumStr(sumCol(curCol)));
    }
}

void Ex2Dialog::delLast(int curCol)
{
    if (currentLine > 0)
    {
        int ex2DelLine = exData->exDelLine[1];
        if (--currentLine == ex2DelLine)
        {
            if (ex2DelLine == 0)
                currentLine = 1;
            else
                --currentLine;
        }
        if (currentLine < 0)
            currentLine = 0;
        if (currentLine < 51)
            exData->ex2Input[curCol][currentLine] = 0;
        ex2LineEdit[curCol]->setText("");
        labelL[curCol]->setText(QString::number(currentLine + 1));
        labelC[curCol]->setText(sumStr(sumCol(curCol)));
    }
    else
    {
        currentLine = 0;
        exData->ex2Input[curCol][currentLine] = 0;
        ex2LineEdit[curCol]->setText("");
        labelL[curCol]->setText(QString::number(currentLine + 1));
        labelC[curCol]->setText(sumStr(sumCol(curCol)));
    }
}

void Ex2Dialog::nextCol(int curCol)
{
    if (QMessageBox::question(this, "提示", "结束计算？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
    {
        if (++curCol >= 3)
        {
            QString msg = "结束练习？";
            if (exData->isExSelected[2])
                msg = "进入下一部分？";
            if (QMessageBox::question(this, "提示", msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
                accept();
            curCol = 2;
        }
        else
        {
            ex2LineEdit[curCol - 1]->setText("");
            ex2LineEdit[curCol - 1]->setEnabled(false);
            labelT[curCol - 1]->setText(labelC[curCol - 1]->text());
            labelL[curCol - 1]->setText("");
            labelC[curCol - 1]->setText("0.00");
            currentLine = 0;
            if (exData->exDelLine[0] == 0)
                currentLine = 1;
            labelL[curCol]->setText(QString::number(currentLine + 1));
            labelC[curCol]->setText(sumStr(sumCol(curCol)));
            ex2LineEdit[curCol]->setEnabled(true);
            ex2LineEdit[curCol]->setFocus();
        }
    }
    else
        ex2LineEdit[curCol]->setFocus();
}

qlonglong Ex2Dialog::sumCol(int col)
{
    if (col < 0 || col > 2)
        return 0;
    qlonglong sum = 0;
    for (int i = 0; i < 51; ++i)
        sum += exData->ex2Input[col][i];
    return sum;
}

QString Ex2Dialog::sumStr(qlonglong sum)
{
    QString str = QString::number(sum / 100).append('.');
    qlonglong ss = sum % 100;
    if (ss < 10)
        str.append('0');
    str.append(QString::number(ss));
    return str;
}

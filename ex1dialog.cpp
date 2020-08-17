#include "ex1dialog.h"
#include "ui_ex1dialog.h"

Ex1Dialog::Ex1Dialog(ExData *exD, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ex1Dialog)
{
    exData = exD;
    currentCol = 0;
    currentLine = 0;
    if (exData->exDelLine[0] == 0)
        currentLine = 1;
    ui->setupUi(this);
    labelBookTotal[0] = ui->label_total_1;
    labelBookTotal[1] = ui->label_total_2;
    labelBookTotal[2] = ui->label_total_3;
    unsigned time_left = exD->timeLeft, minute = (time_left % 3600) / 60, second = time_left % 60;
    QString timestr = QString::number(time_left / 3600).append(':');
    if (minute < 10)
        timestr.append('0');
    timestr.append(QString::number(minute)).append(':');
    if (second < 10)
        timestr.append('0');
    timestr.append(QString::number(second));
    ui->label_time_left->setText(timestr);
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit);
    ui->lineEdit->setValidator(validator);
    connect(ui->lineEdit, SIGNAL(plus()), this, SLOT(plusCur()));
    connect(ui->lineEdit, SIGNAL(del()), this, SLOT(delLast()));
    connect(ui->lineEdit, SIGNAL(next()), this, SLOT(nextCol()));
    if (time_left == 0)
    {
        QMessageBox::question(this, "提示", tr("时间到。"), QMessageBox::Yes, QMessageBox::Yes);
        accept();
    }
    QString noticeStr = "去掉第 ";
    PrepareDialog *prepareDialog = new PrepareDialog(noticeStr.append(QString::number(exData->exDelLine[0] + 1)).append(" 页。"), this);
    prepareDialog->exec();
    showBookNum();
    ui->label_current_t_num->setText(QString::number(currentLine + 1));
    ui->label_total->setText(sumStr(sumCol(currentCol)));
    ui->lineEdit->setFocus();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTimeLeft()));
    timer->start(1000);
}

Ex1Dialog::~Ex1Dialog()
{
    timer->stop();
    delete ui;
}

void Ex1Dialog::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->lineEdit->setCursorPosition(ui->lineEdit->text().size());
}

void Ex1Dialog::showTimeLeft()
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

void Ex1Dialog::plusCur()
{
    QString inputTxt = ui->lineEdit->text();
    if (QString::compare(inputTxt, "") != 0)
    {
        if (currentLine < 51)
            exData->ex1Input[currentCol][currentLine] = inputTxt.toLongLong();
        if (++currentLine == exData->exDelLine[0])
            ++currentLine;
        ui->lineEdit->setText("");
        ui->label_current_t_num->setText(QString::number(currentLine + 1));
        ui->label_total->setText(sumStr(sumCol(currentCol)));
    }
}

void Ex1Dialog::delLast()
{
    if (currentLine > 0)
    {
        int ex1DelLine = exData->exDelLine[0];
        if (--currentLine == ex1DelLine)
        {
            if (ex1DelLine == 0)
                currentLine = 1;
            else
                --currentLine;
        }
        if (currentLine < 0)
            currentLine = 0;
        if (currentLine < 51)
            exData->ex1Input[currentCol][currentLine] = 0;
        ui->lineEdit->setText("");
        ui->label_current_t_num->setText(QString::number(currentLine + 1));
        ui->label_total->setText(sumStr(sumCol(currentCol)));
    }
    else
    {
        currentLine = 0;
        exData->ex1Input[currentCol][currentLine] = 0;
        ui->lineEdit->setText("");
        ui->label_current_t_num->setText(QString::number(currentLine + 1));
        ui->label_total->setText(sumStr(sumCol(currentCol)));
    }
}

void Ex1Dialog::nextCol()
{
    if (QMessageBox::question(this, "提示", "结束计算？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
    {
        labelBookTotal[currentCol]->setText(ui->label_total->text());
        if (++currentCol >= 3)
        {
            QString msg = "进入下一部分？";
            if (exData->selectedExCnt <= 1)
                msg = "结束练习？";
            if (QMessageBox::question(this, "提示", msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
                accept();
            currentCol = 2;
        }
        else
        {
            ui->lineEdit->setText("");
            currentLine = 0;
            if (exData->exDelLine[0] == 0)
                currentLine = 1;
            ui->label_current_t_num->setText(QString::number(currentLine + 1));
            ui->label_total->setText(sumStr(sumCol(currentCol)));
            ui->lineEdit->setFocus();
        }
    }
    else
    {
        ui->lineEdit->setFocus();
    }
    showBookNum();
}

qlonglong Ex1Dialog::sumCol(int col)
{
    if (col < 0 || col > 2)
        return 0;
    qlonglong sum = 0;
    for (int i = 0; i < 51; ++i)
        sum += exData->ex1Input[col][i];
    return sum;
}

QString Ex1Dialog::sumStr(qlonglong sum)
{
    QString str = QString::number(sum / 100).append('.');
    qlonglong ss = sum % 100;
    if (ss < 10)
        str.append('0');
    str.append(QString::number(ss));
    return str;
}

void Ex1Dialog::showBookNum()
{
    QString str = "第 ";
    str.append(QString::number(currentCol + 1)).append(" 本");
    ui->label_current_b_num->setText(str);
}

void Ex1Dialog::accept()
{
    timer->stop();
    QDialog::accept();
}

void Ex1Dialog::reject()
{
    if (QMessageBox::question(this, "提示", "结束练习？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
    {
        timer->stop();
        QDialog::reject();
    }
}

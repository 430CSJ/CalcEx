#include "preparedialog.h"
#include "ui_preparedialog.h"

PrepareDialog::PrepareDialog(QString notice_str, QWidget *parent, unsigned max_time) :
    QDialog(parent),
    ui(new Ui::PrepareDialog)
{
    time_left = max_time;
    ui->setupUi(this);
    ui->label_notice->setText(notice_str);
    unsigned minute = time_left / 60, second = time_left % 60;
    QString timestr;
    if (minute < 10)
        timestr.append("0");
    timestr.append(QString::number(minute));
    timestr.append(':');
    if (second < 10)
        timestr.append('0');
    timestr.append(QString::number(second));
    ui->label_time_left->setText(timestr);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTimeLeft()));
    timer->start(1000);
}

PrepareDialog::~PrepareDialog()
{
    timer->stop();
    delete ui;
}

void PrepareDialog::showTimeLeft()
{
    --time_left;
    unsigned minute = time_left / 60, second = time_left % 60;
    QString timestr;
    if (minute < 10)
        timestr.append("0");
    timestr.append(QString::number(minute));
    timestr.append(':');
    if (second < 10)
        timestr.append('0');
    timestr.append(QString::number(second));
    ui->label_time_left->setText(timestr);
    if (time_left == 0)
    {
        timer->stop();
        accept();
    }
}

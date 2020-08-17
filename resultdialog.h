#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QPalette>
#include "exdata.h"

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(ExData *exD, QWidget *parent);
    ~ResultDialog();

private:
    Ui::ResultDialog *ui;
    ExData *exData;
};

#endif // RESULTDIALOG_H

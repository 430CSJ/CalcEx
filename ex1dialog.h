#ifndef EX1DIALOG_H
#define EX1DIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QRegExpValidator>
#include "exdata.h"
#include "preparedialog.h"
#include "ex1lineedit.h"

namespace Ui {
class Ex1Dialog;
}

class Ex1Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Ex1Dialog(ExData *exD, QWidget *parent);
    ~Ex1Dialog();

private:
    Ui::Ex1Dialog *ui;
    ExData *exData;
    int currentLine, currentCol;
    QTimer *timer;
    QLabel *labelBookTotal[3];
    qlonglong sumCol(int col);
    QString sumStr(qlonglong sum);
    void showBookNum();

protected:
    void reject() override;
    void accept() override;

private slots:
    void showTimeLeft();
    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);
    void plusCur();
    void delLast();
    void nextCol();
};

#endif // EX1DIALOG_H

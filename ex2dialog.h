#ifndef EX2DIALOG_H
#define EX2DIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QRegExpValidator>
#include "exdata.h"
#include "preparedialog.h"
#include "ex2lineedit.h"

namespace Ui {
class Ex2Dialog;
}

class Ex2Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Ex2Dialog(ExData *exD, QWidget *parent);
    ~Ex2Dialog();

protected:
    void accept() override;
    void reject() override;

private slots:
    void on_lineEdit_1_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_3_cursorPositionChanged(int arg1, int arg2);

    void showTimeLeft();
    void plusCur(int curCol);
    void minusCur(int curCol);
    void delLast(int curCol);
    void nextCol(int curCol);

private:
    Ui::Ex2Dialog *ui;
    ExData *exData;
    int currentLine;
    QTimer *timer;
    QLabel *labelC[3], *labelL[3], *labelT[3];
    Ex2LineEdit *ex2LineEdit[3];
    qlonglong sumCol(int col);
    QString sumStr(qlonglong sum);
};

#endif // EX2DIALOG_H

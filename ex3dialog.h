#ifndef EX3DIALOG_H
#define EX3DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QKeyEvent>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QTextCodec>
#include <QScrollBar>
#include "exdata.h"
#include "preparedialog.h"
#include "ex3buylineedit.h"
#include "ex3selllineedit.h"

namespace Ui {
class Ex3Dialog;
}

class Ex3Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Ex3Dialog(ExData *exD, QWidget *parent);
    ~Ex3Dialog();

protected:
    void accept() override;
    void reject() override;

private:
    Ui::Ex3Dialog *ui;
    ExData *exData;
    QTimer *timer;
    QList<Ex3BuyLineEdit*> buyLineEdits;
    QList<Ex3SellLineEdit*> sellLineEdits;

private slots:
    void showTimeLeft();
    void nextB(int i);
    void nextS(int i);
};

#endif // EX3DIALOG_H

#ifndef EX3SELLLINEEDIT_H
#define EX3SELLLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QRegExpValidator>
#include <QTimer>
#include "exdata.h"

class Ex3SellLineEdit: public QLineEdit
{
    Q_OBJECT
public:
    Ex3SellLineEdit();
    explicit Ex3SellLineEdit(QWidget *parent = nullptr);
    int i;
    ExData *exData;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *) override;
    void focusOutEvent(QFocusEvent *) override;
signals:
    void calcS(int i);
private:
    double firstD;
};

#endif // EX3SELLLINEEDIT_H

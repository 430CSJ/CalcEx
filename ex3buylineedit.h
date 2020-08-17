#ifndef EX3BUYLINEEDIT_H
#define EX3BUYLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QRegExpValidator>
#include <QTimer>
#include "exdata.h"

class Ex3BuyLineEdit: public QLineEdit
{
    Q_OBJECT
public:
    Ex3BuyLineEdit();
    explicit Ex3BuyLineEdit(QWidget *parent = nullptr);
    int i;
    ExData *exData;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *) override;
    void focusOutEvent(QFocusEvent *) override;
signals:
    void calcB(int i);
private:
    double firstD;
};

#endif // EX3BUYLINEEDIT_H

#ifndef EX1LINEEDIT_H
#define EX1LINEEDIT_H

#include <QLineEdit>
#include "ex1dialog.h"

class Ex1LineEdit: public QLineEdit
{
    Q_OBJECT
public:
    Ex1LineEdit();
    explicit Ex1LineEdit(QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event);
signals:
    void plus();
    void del();
    void next();
};

#endif // EX1LINEEDIT_H

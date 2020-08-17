#ifndef EX2LINEEDIT_H
#define EX2LINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class Ex2LineEdit: public QLineEdit
{
    Q_OBJECT
public:
    Ex2LineEdit();
    explicit Ex2LineEdit(QWidget *parent = nullptr);
    int colNum;
protected:
    void keyPressEvent(QKeyEvent *event);
signals:
    void plus(int col);
    void minus(int col);
    void del(int col);
    void next(int col);
};

#endif // EX2LINEEDIT_H

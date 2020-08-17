#include "ex2lineedit.h"

Ex2LineEdit::Ex2LineEdit(QWidget *parent) : QLineEdit(parent)
{

}

void Ex2LineEdit::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        emit plus(colNum);
        break;
    case Qt::Key_Minus:
        emit minus(colNum);
        break;
    case Qt::Key_Delete:
        emit del(colNum);
        break;
    case Qt::Key_Enter:
        emit next(colNum);
        break;
    default:
        QLineEdit::keyPressEvent(event);
        break;
    }
}

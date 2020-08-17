#include "ex1lineedit.h"

Ex1LineEdit::Ex1LineEdit(QWidget *parent) : QLineEdit(parent)
{

}

void Ex1LineEdit::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        emit plus();
        break;
    case Qt::Key_Delete:
        emit del();
        break;
    case Qt::Key_Enter:
        emit next();
        break;
    default:
        QLineEdit::keyPressEvent(event);
        break;
    }
}
